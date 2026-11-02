# fetch-cjson.ps1
#
# Downloads the newest cJSON release into resources\vendor\cjson:
#   cJSON.c      the library source (MIT)
#   cJSON.h      its header
#   LICENSE      its license, which travels with the source
#   VERSION.txt  the release tag, so we know exactly what we vendored
#
# Run from this folder with:
#   powershell -ExecutionPolicy Bypass -File .\fetch-cjson.ps1

$ErrorActionPreference = "Stop"
$target = $PSScriptRoot

# GitHub's API returns the newest release. Its tag names the source files at that version.
$headers = @{ "User-Agent" = "training-c-setup" }
$release = Invoke-RestMethod "https://api.github.com/repos/DaveGamble/cJSON/releases/latest" -Headers $headers
$tag = $release.tag_name
Write-Host "Newest cJSON release: $tag"

$base = "https://raw.githubusercontent.com/DaveGamble/cJSON/$tag"
Invoke-WebRequest "$base/cJSON.c" -OutFile (Join-Path $target "cJSON.c") -Headers $headers
Invoke-WebRequest "$base/cJSON.h" -OutFile (Join-Path $target "cJSON.h") -Headers $headers
Invoke-WebRequest "$base/LICENSE" -OutFile (Join-Path $target "LICENSE") -Headers $headers

Set-Content -Path (Join-Path $target "VERSION.txt") -Value "cJSON $tag (source, MIT)"

if ((Get-Item (Join-Path $target "cJSON.c")).Length -lt 20000) {
    throw "cJSON.c is smaller than expected. The download probably failed."
}
Write-Host "Vendored cJSON $tag into $target"
