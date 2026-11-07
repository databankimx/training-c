# setup.ps1
#
# Prepares training-c for the lesson runner (QUICKSTART.md). It can be run from anywhere:
#   0. Checks Git, and clones the repository into C:\Development\training\training-c if this script isn't inside it.
#      Then runs the cloned copy of this script, so every later step uses the repository's own files.
#   1. Checks MSYS2 (C:\msys64), and the UCRT64 toolchain: gcc 14 or later, cmake, and ninja.
#   2. Checks for the WebView2 runtime, and downloads the WebView2 SDK into resources\vendor\webview2.
#   3. Downloads cJSON into resources\vendor\cjson.
#   4. Makes the runner's app.ico from the blue logo, if ImageMagick is installed.
#   5. Configures and builds the lesson runner, in lesson-runner\build.
#
# With -InstallMissing, the script installs what's missing: Git and MSYS2 with winget, and the MSYS2 packages with
# pacman. Installing needs an elevated (Administrator) PowerShell. Safe to run again: anything already in place is
# skipped.
#
# Run from anywhere with:
#   powershell -ExecutionPolicy Bypass -File .\setup.ps1
#   powershell -ExecutionPolicy Bypass -File .\setup.ps1 -InstallMissing

param(
    [switch]$InstallMissing,
    [string]$RepoUrl = "https://github.com/databankimx/training-c.git",
    [string]$Branch = "main"
)

$ErrorActionPreference = "Stop"
$root = $PSScriptRoot
Set-Location $root

$msys = "C:\msys64"
$bin = Join-Path $msys "ucrt64\bin"
$runner = Join-Path $root "lesson-runner"
$defaultRepoPath = "C:\Development\training\training-c"
$gitDefault = "C:\Program Files\Git\cmd\git.exe"
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

function Test-Administrator {
    $identity = [Security.Principal.WindowsIdentity]::GetCurrent()
    $principal = New-Object Security.Principal.WindowsPrincipal($identity)
    return $principal.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Invoke-Winget([string]$id) {
    if (-not (Get-Command winget -ErrorAction SilentlyContinue)) {
        Stop-Setup "winget is not available. Install 'App Installer' from the Microsoft Store, or install $id by hand."
    }
    Write-Host "   winget install -e --id $id" -ForegroundColor Gray
    & winget install -e --id $id --silent --accept-package-agreements --accept-source-agreements
    # winget exit code -1978335189 means the package is already installed, which is fine here.
    if ($LASTEXITCODE -ne 0 -and $LASTEXITCODE -ne -1978335189) {
        Stop-Setup "winget could not install $id (exit code $LASTEXITCODE)."
    }
}

# Runs a command inside the MSYS2 UCRT64 environment, so pacman and the toolchain behave as they do in its shell.
function Invoke-Msys([string]$command) {
    & (Join-Path $msys "usr\bin\bash.exe") -lc "export PATH=/ucrt64/bin:`$PATH; $command"
    return $LASTEXITCODE
}

# Updates MSYS2 until nothing is pending. Upgrading the core runtime closes every MSYS2 process, including the shell that
# runs pacman, so a non-zero exit here is expected. The result is checked instead: is anything still pending?
function Update-Msys2 {
    for ($attempt = 1; $attempt -le 4; $attempt++) {
        Write-Host "   pacman -Syu (pass $attempt)"
        $null = Invoke-Msys "yes | pacman -Syu --noconfirm"
        # pacman -Qu prints one line per pending update, and nothing when the system is up to date.
        $pending = & (Join-Path $msys "usr\bin\bash.exe") -lc "export PATH=/ucrt64/bin:`$PATH; pacman -Qu 2>/dev/null"
        if (-not $pending) {
            return
        }
    }
    Stop-Setup "MSYS2 still has updates pending after 4 passes. Open the MSYS2 UCRT64 shell, run: pacman -Syu, and run this script again."
}

Write-Host ""
Write-Host "training-c setup" -ForegroundColor Yellow

if ($InstallMissing -and -not (Test-Administrator)) {
    Stop-Setup "-InstallMissing needs an elevated PowerShell. Open PowerShell as Administrator, and run the script again."
}

# 0. Git and the repository ------------------------------------------------------------------------------

Write-Step "0. Git and the repository"

$gitExe = $gitDefault
if (-not (Test-Path $gitExe)) {
    $gitCommand = Get-Command git -ErrorAction SilentlyContinue
    if ($gitCommand) { $gitExe = $gitCommand.Source }
}
if (-not (Test-Path $gitExe)) {
    if ($InstallMissing) {
        Write-Host "   Git is missing: installing it"
        Invoke-Winget "Git.Git"
        $gitExe = $gitDefault
    } else {
        Stop-Setup "Git isn't installed. Run this script with -InstallMissing, or install Git from https://git-scm.com."
    }
}
Write-Host "   Git: $gitExe"
$summary["Git"] = "ok"

if (-not (Test-Path (Join-Path $root "QUICKSTART.md"))) {
    # The script is running outside the repository. Clone it, or use the existing clone, then run its copy.
    if (Test-Path (Join-Path $defaultRepoPath "setup.ps1")) {
        Write-Host "   Using the repository at $defaultRepoPath"
        $repoRoot = $defaultRepoPath
    } else {
        Write-Host "   Cloning $RepoUrl ($Branch) into $defaultRepoPath"
        New-Item -ItemType Directory -Force -Path (Split-Path $defaultRepoPath -Parent) | Out-Null
        & $gitExe clone --branch $Branch $RepoUrl $defaultRepoPath
        if ($LASTEXITCODE -ne 0) {
            Stop-Setup "git clone failed (exit code $LASTEXITCODE). Check the address, and your access to the repository."
        }
        $repoRoot = $defaultRepoPath
    }
    Write-Host "   Continuing from the repository at $repoRoot"
    $childParams = @{}
    if ($InstallMissing) { $childParams["InstallMissing"] = $true }
    & (Join-Path $repoRoot "setup.ps1") @childParams
    exit $LASTEXITCODE
}

if (-not $root.StartsWith("C:\Development\", [StringComparison]::OrdinalIgnoreCase)) {
    # QUICKSTART asks for the repository under C:\Development. Security software may remove programs built elsewhere.
    Add-Warning "the repository is at $root, not under C:\Development. See QUICKSTART, 'Where to clone the repository'."
}
$summary["Repository"] = $root

# 1. Toolchain ------------------------------------------------------------------------------------------

Write-Step "1. MSYS2 UCRT64 toolchain (gcc 14 or later, cmake, ninja)"
if (-not (Test-Path (Join-Path $msys "ucrt64"))) {
    if ($InstallMissing) {
        Write-Host "   MSYS2 is missing: installing it"
        Invoke-Winget "MSYS2.MSYS2"
        if (-not (Test-Path (Join-Path $msys "ucrt64"))) {
            Stop-Setup "MSYS2 was installed, but it isn't in C:\msys64. Check where winget put it, then run this script again."
        }
    } else {
        Stop-Setup ("MSYS2 isn't installed in C:\msys64. Run this script with -InstallMissing, or install it from " +
            "https://www.msys2.org, then open the MSYS2 UCRT64 shell and run: pacman -Syu")
    }
}

# The toolchain's folder goes first on PATH, for this script and for the programs it starts.
$env:Path = "$bin;$env:Path"

$missing = @()
if (-not (Test-Path (Join-Path $bin "gcc.exe"))) { $missing += "mingw-w64-ucrt-x86_64-gcc" }
if (-not (Test-Path (Join-Path $bin "cmake.exe"))) { $missing += "mingw-w64-ucrt-x86_64-cmake" }
if (-not (Test-Path (Join-Path $bin "ninja.exe"))) { $missing += "mingw-w64-ucrt-x86_64-ninja" }
if (-not (Test-Path (Join-Path $bin "rsvg-convert.exe"))) { $missing += "mingw-w64-ucrt-x86_64-librsvg" }
if (-not (Test-Path (Join-Path $bin "magick.exe"))) { $missing += "mingw-w64-ucrt-x86_64-imagemagick" }

if ($missing.Count -gt 0) {
    $list = $missing -join " "
    if ($InstallMissing) {
        # A freshly installed MSYS2 has an out-of-date package database, so update it before installing anything.
        Update-Msys2
        Write-Host "   Installing: $list"
        if ((Invoke-Msys "yes | pacman -S --needed --noconfirm $list") -ne 0) {
            Stop-Setup "pacman couldn't install: $list. Check the output above."
        }
    } else {
        Stop-Setup ("These packages are missing: $list. Run this script with -InstallMissing, or install them " +
            "from the MSYS2 UCRT64 shell with: pacman -S --needed $list")
    }
}

$version = (& (Join-Path $bin "gcc.exe") --version | Select-Object -First 1)
if ($version -match "(\d+)\.\d+") {
    $gccMajor = [int]$Matches[1]
} else {
    Stop-Setup "Couldn't read the gcc version: $version"
}
if ($gccMajor -lt 14) {
    Stop-Setup "gcc $gccMajor was found, but the course needs gcc 14 or later. Run: pacman -Syu"
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

$sdkHeader = Join-Path $root "resources\vendor\webview2\sdk\build\native\include\WebView2.h"
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
