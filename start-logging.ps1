adb shell am force-stop com.beatgames.beatsaber
adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
$bspid = adb shell pidof com.beatgames.beatsaber
while ([string]::IsNullOrEmpty($bspid)) {
    Start-Sleep -Milliseconds 100
    $bspid = adb shell pidof com.beatgames.beatsaber
}
if ($args.Count -eq 0) {
    echo "Start logging!"
    adb logcat -T "$timestamp" --pid $bspid 
}
if ($args[0] -eq "--file") {
    echo "Logging and saving to file!"
    (adb logcat -T "$timestamp" --pid $bspid | Select-String -pattern "(QuestHook|modloader|AndroidRuntime)") | Tee-Object -FilePath $PSScriptRoot/logcat.log 
}
if ($args[0] -eq "--log") {
    echo "Logging and saving to file!"
    adb logcat -T "$timestamp" --pid $bspid > $PSScriptRoot/logcat.log 
}
