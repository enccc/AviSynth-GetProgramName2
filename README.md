# GetProgramName2
    a plugin for AviSynth

## Requirements

    Avisynth2.6.0 / Avisynth+ (AviSynth 2.5.x is not supported)
        tested on AviSynth+ MT by pinterf only

    Windows7 SP1 / 8.1 / 10
        tested on Windows10 Pro 64bit Japanese Edition only

## GetProgramName2.dll

### GetProgramName2(bool "full_path")

    returns a program name calling the avisynth script.

    bool full_path (default: false)
        if false, returns a program name only.
        if true, returns a full path.

## GetProgramName2_Util.avsi

### GetProgramName(bool "full_path")
    an alias for GetProgramName2().

### GetProgramDir()
    returns a path excluding a program name from a full path.

## LICENSE
MIT LICENSE

## NOTE
GetProgramName2 is similar to GetProgramName by JM Roelofs,  
but this plugin is a newly written.  
so... this plugin might be really buggy.  
