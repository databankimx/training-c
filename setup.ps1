# setup.ps1
#
# Prepares a fresh copy of training-c for the lesson runner (QUICKSTART.md):
#   1. Checks the MSYS2 UCRT64 toolchain: gcc 14 or later, cmake, and ninja.
#   2. Checks for the WebView2 runtime, and downloads the WebView2 SDK into resources\vendor\webview2.
#   3. Downloads cJSON into resources\vendor\cjson.
#   4. Makes the runner's app.ico from the blue logo, if ImageMagick is installed.
#   5. Configures and builds the lesson runner, in lesson-runner\build.
#
# With -InstallMissing, the script installs the missing MSYS2 packages with pacman.
# Safe to run again: anything already in place is skipped.
#
# Run from the repository root with:
#   powershell -ExecutionPolicy Bypass -File .\setup.ps1
#   powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing

param(
    [switch]$InstallMissing
)

$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
Set-Location $root

$msys = "C:\msys64"
$bin = Join-Path $msys "ucrt64\bin"
$runner = Join-Path $root "lesson-runner"
$summary = [ordered]@{}

function Write-Step([string]$title) {
    Write-Host ""
    Write-Host "== $title ==" -ForegroundColor Cyan
}

function Stop-Setup([string]$message) {
    Write-Host ""
    Write-Host "SETUP STOPPED: $message" -ForegroundColor Red
    Write-Host "Fix the problem above, then run this script again. Steps already done are skipped."
    exit 1
}

function Add-Warning([string]$message) {
    Write-Host "   WARNING: $message" -ForegroundColor Yellow
}

# Runs a command inside the MSYS2 UCRT64 environment, so pacman and the toolchain behave as they do in its shell.
function Invoke-Msys([string]$command) {
    & (Join-Path $msys "usr\bin\bash.exe") -lc $command
    return $LASTEXITCODE
}

# The toolchain's folder goes first on PATH, for this script and for the programs it starts.
if (Test-Path $bin) {
    $env:Path = "$bin;$env:Path"
}

# 1. Toolchain ------------------------------------------------------------------------------------------

Write-Step "1. MSYS2 UCRT64 toolchain (gcc 14 or later, cmake, ninja)"
if (-not (Test-Path (Join-Path $msys "ucrt64"))) {
    Stop-Setup ("MSYS2 isn't installed in C:\msys64. Install it from https://www.msys2.org, then open the " +
        "MSYS2 UCRT64 shell and run: pacman -Syu")
}

$missing = @()
if (-not (Test-Path (Join-Path $bin "gcc.exe"))) { $missing += "mingw-w64-ucrt-x86_64-gcc" }
if (-not (Test-Path (Join-Path $bin "cmake.exe"))) { $missing += "mingw-w64-ucrt-x86_64-cmake" }
if (-not (Test-Path (Join-Path $bin "ninja.exe"))) { $missing += "mingw-w64-ucrt-x86_64-ninja" }
if (-not (Test-Path (Join-Path $bin "rsvg-convert.exe"))) { $missing += "mingw-w64-ucrt-x86_64-librsvg" }
if (-not (Test-Path (Join-Path $bin "magick.exe"))) { $missing += "mingw-w64-ucrt-x86_64-imagemagick" }

if ($missing.Count -gt 0) {
    $list = $missing -join " "
    if ($InstallMissing) {
        Write-Host "   Installing: $list"
        if ((Invoke-Msys "pacman -S --needed --noconfirm $list") -ne 0) {
            Stop-Setup "pacman couldn't install: $list. Check the output above."
        }
    } else {
        Stop-Setup ("These packages are missing: $list. Run this script with -InstallMissing, or install them " +
            "from the MSYS2 UCRT64 shell with: pacman -S --needed $list")
    }
}

$version = (& (Join-Path $bin "gcc.exe") --version | Select-Object -First 1)
if ($version -notmatch "(\d+)\.\d+") { Stop-Setup "Couldn't read the gcc version: $version" }
if ([int]$Matches[1] -lt 14) {
    Stop-Setup "gcc $($Matches[1]) was found, but the course needs gcc 14 or later. Run: pacman -Syu"
}
Write-Host "   $version"
$summary["Toolchain"] = "ok"

# 2. WebView2 ------------------------------------------------------------------------------------------

Write-Step "2. WebView2 runtime and SDK"
$runtime = Get-ItemProperty "HKLM:\SOFTWARE\WOW6432Node\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}" -ErrorAction SilentlyContinue
if ($runtime -and $runtime.pv) {
    Write-Host "   WebView2 Runtime $($runtime.pv) is installed."
    $summary["WebView2 runtime"] = "ok"
} else {
    Add-Warning "The WebView2 Runtime wasn't found. Windows 11 includes it. Otherwise install the Evergreen Bootstrapper from https://developer.microsoft.com/microsoft-edge/webview2/"
    $summary["WebView2 runtime"] = "missing"
}

$sdkDir = Join-Path $root "resources\vendor\webview2\sdk"
$sdkHeader = Join-Path $sdkDir "build\native\include\WebView2.h"
if (Test-Path $sdkHeader) {
    Write-Host "   The WebView2 SDK is already in resources\vendor\webview2\sdk."
} else {
    Write-Host "   Downloading the WebView2 SDK from NuGet..."
    $fetch = Join-Path $root "resources\vendor\webview2\fetch-webview2.ps1"
    if (-not (Test-Path $fetch)) { Stop-Setup "The fetch script wasn't found at $fetch." }
    & powershell -ExecutionPolicy Bypass -File $fetch
    if ($LASTEXITCODE -ne 0) { Stop-Setup "The WebView2 SDK download failed. Check the messages above." }
    if (-not (Test-Path $sdkHeader)) { Stop-Setup "The SDK was unpacked, but WebView2.h isn't where the build expects it." }
    Write-Host "   The SDK is in resources\vendor\webview2\sdk."
}
$summary["WebView2 SDK"] = "ok"

# 3. cJSON -----------------------------------------------------------------------------------------------

Write-Step "3. cJSON (vendored source)"
$cjsonDir = Join-Path $root "resources\vendor\cjson"
if (Test-Path (Join-Path $cjsonDir "cJSON.c")) {
    Write-Host "   cJSON.c is already in resources\vendor\cjson."
} else {
    & powershell -ExecutionPolicy Bypass -File (Join-Path $cjsonDir "fetch-cjson.ps1")
    if ($LASTEXITCODE -ne 0) { Stop-Setup "The cJSON download failed. Check the messages above." }
}
$summary["cJSON"] = "ok"

# 4. Icon ------------------------------------------------------------------------------------------------

Write-Step "4. Title-bar icon (app.ico)"
$icon = Join-Path $runner "host\app.ico"
$logo = Join-Path $root "resources\Icon_Blue.svg"
if (Test-Path $icon) {
    Write-Host "   app.ico is already in place."
    $summary["Icon"] = "ok"
} elseif (-not (Test-Path $logo)) {
    Add-Warning "resources\Icon_Blue.svg wasn't found, so app.ico can't be made. The runner will build without a title-bar icon."
    $summary["Icon"] = "skipped"
} else {
    $code = Invoke-Msys ("magick -background none '$(($logo -replace '\\','/'))' -define icon:auto-resize=256,48,32,16 '$(($icon -replace '\\','/'))'")
    if ($code -eq 0 -and (Test-Path $icon)) {
        Write-Host "   Made app.ico."
        $summary["Icon"] = "ok"
    } else {
        Add-Warning "app.ico couldn't be made. Check that ImageMagick and librsvg are installed, then run this script again."
        $summary["Icon"] = "missing"
    }
}

# 5. Build the runner ------------------------------------------------------------------------------------

Write-Step "5. Lesson runner build"
Push-Location $runner
try {
    & cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    if ($LASTEXITCODE -ne 0) { Stop-Setup "CMake configure failed. Check the messages above." }
    & cmake --build build
    if ($LASTEXITCODE -ne 0) { Stop-Setup "The runner build failed. Check the messages above." }
} finally {
    Pop-Location
}

# The editor's C settings, so IntelliSense matches the build (C17, gcc, and the runner's compile commands).
$vscodeDir = Join-Path $root ".vscode"
$propsFile = Join-Path $vscodeDir "c_cpp_properties.json"
if (-not (Test-Path $propsFile)) {
    New-Item -ItemType Directory -Force $vscodeDir | Out-Null
    @'
{
  "version": 4,
  "configurations": [
    {
      "name": "MSYS2 UCRT64 gcc",
      "compileCommands": "${workspaceFolder}/lesson-runner/build/compile_commands.json",
      "includePath": [
        "${default}",
        "${workspaceFolder}/**",
        "${workspaceFolder}/resources/vendor/cjson"
      ],
      "cStandard": "c17",
      "intelliSenseMode": "windows-gcc-x64",
      "compilerPath": "C:/msys64/ucrt64/bin/gcc.exe"
    }
  ]
}
'@ | Set-Content -Path $propsFile -Encoding UTF8
    Write-Host "   Wrote .vscode\c_cpp_properties.json"
}

$summary["Lesson runner"] = "built (lesson-runner\build)"

# Summary -----------------------------------------------------------------------------------------------

Write-Step "Summary"
foreach ($item in $summary.GetEnumerator()) {
    Write-Host ("   {0,-22} {1}" -f $item.Key, $item.Value)
}
Write-Host ""
Write-Host "Setup finished. To start the lesson runner:" -ForegroundColor Green
Write-Host "   cd lesson-runner"
Write-Host "   .\build\lesson-runner.exe"
