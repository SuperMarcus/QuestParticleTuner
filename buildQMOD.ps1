$mod = "./mod.json"
$modJson = Get-Content $mod -Raw | ConvertFrom-Json

$env:qmodName = $modJson.name
$env:module_id = $modJson.id
$qmodVersion = $modJson.version

$qmod = $env:qmodName + "-v" + $qmodVersion + ".qmod"


$allLibs = Get-ChildItem ./libs/arm64-v8a/*.so | Select -Expand Name

$cover = "./" + $modJson.coverImage

$fileList = @($cover, $mod)

$bannedLibList = "libmodloader.so libquestui.so libcodegen.so libcustom-types.so"

# Creates the list of Modfiles and Library files
$modlib = @()
$libs = @()
foreach ($lib in $allLibs) {
    if (!($bannedLibList.Contains($lib))) {
        $path = "./libs/arm64-v8a/" + $lib;
        $fileList += , $path;
        if ($lib.Contains($env:module_id.ToLower())){
            $modlib += , $lib;
        }
        else {
            $libs += , $lib
                    
        }
    }
}


$extraFiles = @()
if (Test-Path "./ExtraFiles") {
    $extraEntries = Get-ChildItem ./ExtraFiles/* -Recurse

    foreach ($entry in $extraEntries) {
        $mode = $entry | Select -Expand Mode
        if ($mode.Contains("d")) {
            continue
        }

        # if not a dir
        if (-not $entry.Directory.Name.Contains("ExtraFiles")) {
            $dir = $entry.Directory
            $folderPath = $dir.Name + "/" + $entry.Name
            while (($dir.Directory) -and (-not $dir.Directory.Name.Contains("ExtraFiles"))) {
                $folderPath = $dir.Directory.Name + "/" + $folderPath
            }

            if ($folderPath.Contains("Icons")) {
                continue;
            }
            $extraFiles += , $folderPath
        }
        else {
            $extraFiles += , $entry.Name
        }
    }

    foreach ($file in $extraFiles) {
        $path = "./ExtraFiles/" + $file
        $fileList += , $path
    } 
}
else {
    echo "No ExtraFiles Directory Found"
}

# add the thing to the libs list because we don't need it as a mod file
$modJson.modFiles = $modlib
$modJson.libraryFiles = $libs

$modText = $modJson | ConvertTo-Json -depth 32
echo $modText
Set-Content $mod $modText

# if the qmod exists, rename it to zip to update it, we'll rename it back later
if (Test-Path $qmod) {
    Remove-Item -Force $qmod
}
$msg = "Creating qmod for module " + $env:module_id + " With name " + $qmod
echo $msg
echo $fileList
Compress-Archive -Path $fileList -DestinationPath ./temp.zip
& move-item -Force ./temp.zip $qmod
echo "Task Completed"
