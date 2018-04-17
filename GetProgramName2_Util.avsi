/*
    GetProgramName2_Util.avsi v0.1.0

    GetProgramName(bool "full_path")
        an alias for GetProgramName2().

    GetProgramDir()
        returns a path excluding a program name from a full path.
*/

function GetProgramName(bool "full_path")
{
    full_path = Default(full_path, false)
    return GetProgramName2(full_path)
}

function GetProgramDir()
{
    prog_name = GetProgramName2(full_path=false)
    full_path = GetProgramName2(full_path=true)
    strlength = StrLen(full_path) - StrLen(prog_name)
    return MidStr(full_path, 1, strlength)
}
