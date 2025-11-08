#include "sysfunc_impl.h"
#include <windows.h>
#include <rpc.h>

void WindowsSysFunc::execute(const ttstr &program, const ttstr &params)
{
    ttstr system_text;
    system_text += program;
    if (!params.IsEmpty()) {
        system_text += TJS_W(" ");
        system_text += params;
    }

    std::string narrow_text;
    TVPUtf16ToUtf8(narrow_text, system_text.AsStdString());
    system(narrow_text.c_str());
}

bool WindowsSysFunc::create_app_lock(const ttstr &lockname)
{
    return true;
}

unsigned long long WindowsSysFunc::get_tick_time()
{
    return GetTickCount64();
}

ttstr WindowsSysFunc::get_uuid()
{
    UUID uuid_win;
    RPC_CSTR uuid_str;
    UuidCreate(&uuid_win);
    UuidToStringA(&uuid_win, &uuid_str);

    ttstr result = reinterpret_cast<const char*>(uuid_str);
    RpcStringFreeA(&uuid_str);
    return result;
}
