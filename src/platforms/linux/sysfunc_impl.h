#pragma once
#include <map>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/utsname.h>

#include "interfaces/sysfunc.h"


class UnixSysFunc : public LibRuntime::Interfaces::SysFuncFallbackImpl {
public:
    bool create_app_lock(const tjs_char *lockname) override;
    void release_all_app_lock();
    void get_os_name(ttstr &os_name) override;

private:
    std::map<int, std::string> app_locks;
};