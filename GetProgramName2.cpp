#include <avisynth.h>
#include <windows.h>

AVSValue __cdecl GetProgramName2(AVSValue args, void *user_data, IScriptEnvironment *env)
{
    bool  full_path = args[0].AsBool(false);

    char  path_str[MAX_PATH*2]; /* [MAX_PATH*2]: for 2-byte character */
    char *path_ptr;
    int   ret_code;

    ret_code = GetModuleFileName(NULL, path_str, sizeof(path_str));
    if(ret_code == 0)
        env->ThrowError("GetProgramName2: Failed to GetModuleFileName");

    path_ptr = path_str;
    if(full_path == false)
    {
        path_ptr = strrchr(path_str, '\\');
        if(path_ptr[0] == '\\')
            path_ptr++;
        if(path_ptr == NULL)
            path_ptr = path_str;
    }

    return AVSValue(env->SaveString(path_ptr));
}

const AVS_Linkage* AVS_linkage = 0;

extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment* env, const AVS_Linkage* const vectors)
{
    AVS_linkage = vectors;

    env->AddFunction("GetProgramName2", "[full_path]b", GetProgramName2, 0);

    return "GetProgramName2 v0.2.0";
}
