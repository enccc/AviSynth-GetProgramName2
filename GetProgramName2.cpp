#include <avisynth.h>
#include <windows.h>

AVSValue __cdecl GetProgramName2(AVSValue args, void *user_data, IScriptEnvironment *env)
{
    bool    full_path = args[0].AsBool(false) ? false : true;

    char    path_mbs[MAX_PATH*2];  /* [MAX_PATH*2]: for 2-byte character */
    char   *path_pos;
    int     return_code;
    int     mbs_len = MAX_PATH*2;

    int     cmd_argc;
    LPWSTR* cmd_argv = CommandLineToArgvW(GetCommandLineW(), &cmd_argc );

    if(cmd_argv == NULL)
        env->ThrowError("GetProgramName2: Failed to get the command line arguments");

    if(cmd_argv[0] != NULL)
    {
        return_code = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, cmd_argv[0], -1, path_mbs, mbs_len, NULL, NULL);
        if(return_code == 0)
            env->ThrowError("GetProgramName2: Failed to WideCharToMultiByte");
    }

    path_pos = path_mbs;
    if(full_path)
    {
        path_pos = strrchr(path_mbs, '\\') + 1;
    }

    return AVSValue(env->SaveString(path_pos));
}

const AVS_Linkage* AVS_linkage = 0;

extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment* env, const AVS_Linkage* const vectors)
{
    AVS_linkage = vectors;

    env->AddFunction("GetProgramName2", "[full_path]b", GetProgramName2, 0);

    return "GetProgramName2 v0.1.0";
}
