#include "sysfunc_impl.h"

bool UnixSysFunc::create_app_lock(const ttstr &lockname) {
    std::string str;
    TVPUtf16ToUtf8(str, lockname.c_str());

    str += ".sock";

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    sockaddr_un addr = {};
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, str.c_str(), sizeof(addr.sun_path) - 1);

    if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        close(sock);
        return false;
    }

    app_locks[sock] = str;
    return true;
}

void UnixSysFunc::release_all_app_lock() {
    for (const auto& app_lock: app_locks) {
        close(app_lock.first);
        unlink(app_lock.second.c_str());
    }
}
