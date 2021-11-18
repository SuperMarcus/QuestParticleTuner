# ██████╗ ██╗   ██╗██╗██╗     ██████╗ 
# ██╔══██╗██║   ██║██║██║     ██╔══██╗
# ██████╔╝██║   ██║██║██║     ██║  ██║
# ██╔══██╗██║   ██║██║██║     ██║  ██║
# ██████╔╝╚██████╔╝██║███████╗██████╔╝



if(!(Test-Path ./ndkpath.txt)){
    Write-Host "Please create the ndkpath.txt file with the path to the Android NDK."
    exit
}
$NDKPath = Get-Content ./ndkpath.txt -First 1


# Get Mod data from QPM.JSON
echo "Reading QMOD data from qpm.json"
$qpmJson = Get-Content ./qpm.json -raw | ConvertFrom-Json
$modID = $qpmJson.info.id
$modName = $qpmJson.info.name   
$ver = $qpmJson.info.version
$buildlevel = (Get-Date -format "yyMMdd")
$Version = $ver + "-" + (Get-Date -format "yyMMdd")
$numDependencies = $qpmJson.dependencies.Count
for ($i = 0; $i -lt $numDependencies; $i++) {
    $dep = $qpmJson.dependencies[$i]
    if ($dep.id -eq "beatsaber-hook") {
        $BSHook = $qpmJson.dependencies[$i].versionRange
        break
    }
}
$modfile = "lib" + $modID.ToLower() + ".so"
$BSHookfile = "libbeatsaber-hook_" + $BSHook.Replace(".", "_") + ".so"
$qmodfile = $modID + "-v" + $Version + ".qmod"

echo "Mod name:        $modName"
echo "Mod ID:          $modID"
echo "Mod version:     $ver"
echo "Mod build:       $buildlevel"
echo "BS-Hook version: $BSHook"
echo "Mod lib file:    $modfile"
echo "BS-Hook file:    $BSHookfile"
echo "Qmod file:       $qmodfile"
echo ""

# Injects changes in MOD.JSON
echo "Updating mod.json..."
$modJson = Get-Content ./mod.json -raw | ConvertFrom-Json
$modJson.id = $modID
$modJson.name = $modName
$modJson.version = $Version
$numDependencies = $modJson.libraryFiles.Count
for ($i = 0; $i -lt $numDependencies; $i++) {
    $lib = $modJson.libraryFiles[$i]
    $pos = $lib.IndexOf("libbeatsaber-hook")
    if ($pos -ge 0) {
        $modJson.libraryFiles[$i] = $BSHookfile
        break
    }
}
$modJson | ConvertTo-Json -depth 32 | Set-Content ./mod.json
echo "mod.json updated."


if ((Test-Path "./extern/beatsaber-hook/src/inline-hook/And64InlineHook.cpp", "./extern/beatsaber-hook/src/inline-hook/inlineHook.c", "./extern/beatsaber-hook/src/inline-hook/relocate.c") -contains $false) {
    Write-Host "Critical: Missing inline-hook"
    if (!(Test-Path "./extern/beatsaber-hook/src/inline-hook/And64InlineHook.cpp")) {
        Write-Host "./extern/beatsaber-hook/src/inline-hook/And64InlineHook.cpp"
    }
    if (!(Test-Path "./extern/beatsaber-hook/src/inline-hook/inlineHook.c")) {
        Write-Host "./extern/beatsaber-hook/src/inline-hook/inlineHook.c"
    }
    if (!(Test-Path "./extern/beatsaber-hook/inline-hook/src/relocate.c")) {
        Write-Host "./extern/beatsaber-hook/src/inline-hook/relocate.c"
    }
    Write-Host "Task Failed"
    exit 1;
}


$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

$modlib = $modID.ToLower()
$BSHook = $BSHook.Replace(".", "_")
# Read-Host "ready to build $modfile. Press ENTER key to continue..."
echo "Building $modfile Version: $Version ..."
& $buildScript NDK_DEBUG=0 NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk VERSION=$Version MODID=$modID LIBNAME=$modLib BSHOOK=$BSHook -Oline
Write-Host "Build complete."
Write-Host "Debug lib file:   ./obj/local/arm64-v8a/$modfile"
Write-Host "Release lib file: ./libs/arm64-v8a/$modfile"