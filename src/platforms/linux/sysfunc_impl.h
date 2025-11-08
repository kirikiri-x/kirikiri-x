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
    bool create_app_lock(const ttstr &lockname) override;
    void release_all_app_lock();

private:
    std::map<int, std::string> app_locks;
};