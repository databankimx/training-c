# fetch-webview2.ps1
#
# Downloads the newest stable Microsoft.Web.WebView2 package from NuGet, and unpacks it into .\sdk.
# The package holds the C header (WebView2.h) and the loader DLL (WebView2Loader.dll) that the lesson runner needs.
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\fetch-webview2.ps1

$ErrorActionPreference = "Stop"
$package = "microsoft.web.webview2"
$sdk = Join-Path $PSScriptRoot "sdk"

# NuGet publishes a list of every version of a package. The last stable version (no '-' suffix) is the newest.
$index = Invoke-RestMethod "https://api.nuget.org/v3-flatcontainer/$package/index.json"
$version = $index.versions | Where-Object { $_ -notmatch "-" } | Select-Object -Last 1
Write-Host "Newest stable WebView2 SDK on NuGet: $version"

$url = "https://api.nuget.org/v3-flatcontainer/$package/$version/$package.$version.nupkg"
$zip = Join-Path $env:TEMP "webview2-$version.zip"
Write-Host "Downloading $url"
Invoke-WebRequest $url -OutFile $zip

# A .nupkg is a zip file. Expand-Archive needs the .zip extension, which the download already has.
if (Test-Path $sdk) {
    Remove-Item $sdk -Recurse -Force
}
Expand-Archive -Path $zip -DestinationPath $sdk -Force

$header = Join-Path $sdk "build\native\include\WebView2.h"
$loader = Join-Path $sdk "build\native\x64\WebView2Loader.dll"
if ((Test-Path $header) -and (Test-Path $loader)) {
    Write-Host "Unpacked WebView2 $version into $sdk"
    Write-Host "   header: build\native\include\WebView2.h"
    Write-Host "   loader: build\native\x64\WebView2Loader.dll"
} else {
    throw "The package didn't contain the expected files. Look in $sdk for the layout NuGet used."
}

# The WebView2 Runtime is what actually renders the page. Windows 11 includes it, and Windows 10 usually has it.
$runtime = Get-ItemProperty "HKLM:\SOFTWARE\WOW6432Node\Microsoft\EdgeUpdate\Clients\{F3017226-FE2A-4295-8BDF-00C3A9A7E4C5}" -ErrorAction SilentlyContinue
if ($runtime -and $runtime.pv) {
    Write-Host "WebView2 Runtime $($runtime.pv) is installed."
} else {
    Write-Host "WARNING: the WebView2 Runtime wasn't found. Install it from https://developer.microsoft.com/microsoft-edge/webview2/ (the Evergreen Bootstrapper)." -ForegroundColor Yellow
}
