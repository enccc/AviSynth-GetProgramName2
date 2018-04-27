#include <avisynth.h>
#include <windows.h>

AVSValue __cdecl GetProgramName2(AVSValue args, void *user_data, IScriptEnvironment *env)
{
    bool     full_path = args[0].AsBool(false);

    wchar_t  path_wcs[MAX_PATH*2];  /* [MAX_PATH*2]: for surrogate pair characters */
    wchar_t *path_ptr;
    char     path_str[MAX_PATH*2];
    int      ret_code;

    ret_code = GetModuleFileNameW(NULL, path_wcs, MAX_PATH*2);
    if(ret_code == 0)
        env->ThrowError("GetProgramName2: Failed to get a program full path");

    path_ptr = path_wcs;
    if(full_path == false)
    {
        path_ptr = wcsrchr(path_wcs, L'\\');
        if(path_ptr[0] == L'\\')
            path_ptr++;
        if(path_ptr == NULL)
            path_ptr = path_wcs;
    }

    ret_code = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, path_ptr, -1, path_str, MAX_PATH*2, NULL, NULL);
    if(ret_code == 0)
        env->ThrowError("GetProgramName2: Failed to convert to multi byte chars from wide byte chars");

    return AVSValue(env->SaveString(path_str));
}

const AVS_Linkage* AVS_linkage = 0;

extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment* env, const AVS_Linkage* const vectors)
{
    AVS_linkage = vectors;

    env->AddFunction("GetProgramName2", "[full_path]b", GetProgramName2, 0);

    return "GetProgramName2 v0.3.0";
}
