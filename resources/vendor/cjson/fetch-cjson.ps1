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

# Pinned release. To move to a newer cJSON, change $tag and the three hashes below, after checking the release notes.
$tag = "v1.7.19"
$expected = @{
    "cJSON.c" = "298581a04a36c0165da4b0aade235c23088cb2faa58651d720ea2f3706ed0b0d"
    "cJSON.h" = "25b0145150d500498e4d209cec69c18c42cf818bffcc54690be3b895a2a16dee"
    "LICENSE" = "a36dda207c36db5818729c54e7ad4e8b0c6fba847491ba64f372c1a2037b6d5c"
}
Write-Host "Pinned cJSON release: $tag"

$headers = @{ "User-Agent" = "training-c-setup" }
$base = "https://raw.githubusercontent.com/DaveGamble/cJSON/$tag"
foreach ($name in $expected.Keys) {
    $file = Join-Path $target $name
    Invoke-WebRequest "$base/$name" -OutFile $file -Headers $headers
    $actual = (Get-FileHash $file -Algorithm SHA256).Hash.ToLowerInvariant()
    if ($actual -ne $expected[$name]) {
        Remove-Item $file -Force
        throw "$name failed its SHA-256 check. Expected $($expected[$name]), got $actual. Nothing was kept."
    }
}

Set-Content -Path (Join-Path $target "VERSION.txt") -Value "cJSON $tag (source, MIT). Files checked against SHA-256 when downloaded."

if ((Get-Item (Join-Path $target "cJSON.c")).Length -lt 20000) {
    throw "cJSON.c is smaller than expected. The download probably failed."
}
Write-Host "Vendored cJSON $tag into $target"
