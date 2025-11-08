#pragma once
#include <interfaces/sysfunc.h>

#include "interfaces/filesystem.h"

class WindowsSysFunc: public LibRuntime::Interfaces::ISysFunc {
public:
    void execute(const ttstr &program, const ttstr &params) override;
    bool create_app_lock(const ttstr &lockname) override;
    unsigned long long get_tick_time() override;
    ttstr get_uuid() override;
};
