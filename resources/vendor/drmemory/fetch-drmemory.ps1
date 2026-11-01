# fetch-drmemory.ps1
#
# Downloads the newest Dr. Memory release for Windows from GitHub, and unpacks it into .\install.
# Dr. Memory is a memory checker for Windows programs built with MinGW. It finds leaks, double frees, and use after
# free, which are the errors the dynamic-memory lesson covers.
#
# Licence: Dr. Memory is licensed under LGPL 2.1, with BSD-licensed modules. The licence was approved for use on
# 10/31/2026. Only this script is stored in the repository. The download itself is ignored by git, so no copy of the
# tool is redistributed.
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\fetch-drmemory.ps1

$ErrorActionPreference = "Stop"
$target = Join-Path $PSScriptRoot "install"
$headers = @{ "User-Agent" = "training-c-setup" }

$release = Invoke-RestMethod "https://api.github.com/repos/DynamoRIO/drmemory/releases/latest" -Headers $headers
$tag = $release.tag_name
Write-Host "Newest Dr. Memory release: $tag"

# The Windows package is a zip file whose name contains "Windows". Pick the first one.
$asset = $release.assets | Where-Object { $_.name -match "Windows.*\.zip$" } | Select-Object -First 1
if (-not $asset) {
    throw "No Windows zip was found in release $tag. Check the release page at https://github.com/DynamoRIO/drmemory/releases."
}

$zip = Join-Path $env:TEMP $asset.name
Write-Host "Downloading $($asset.name)..."
Invoke-WebRequest $asset.browser_download_url -OutFile $zip -Headers $headers

if (Test-Path $target) {
    Remove-Item $target -Recurse -Force
}
New-Item -ItemType Directory -Force $target | Out-Null
Expand-Archive -Path $zip -DestinationPath $target -Force

# The package unpacks into a folder of its own, so find the program wherever it landed.
$exe = Get-ChildItem $target -Recurse -Filter "drmemory.exe" | Select-Object -First 1
if (-not $exe) {
    throw "drmemory.exe wasn't found after unpacking. Look in $target for the layout the package used."
}
Set-Content -Path (Join-Path $target "VERSION.txt") -Value "Dr. Memory $tag, from $($asset.name)"
Write-Host "Installed Dr. Memory $tag. The program is at $($exe.FullName)"
