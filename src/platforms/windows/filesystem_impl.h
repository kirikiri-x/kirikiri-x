#pragma once
#include "interfaces/filesystem.h"

class WindowsFileSystem: public LibRuntime::Interfaces::IFileSystem {
public:
    size_t get_current_directory(ttstr &result) override;
    bool set_current_directory(const ttstr &path) override;

    tTJSBinaryStream *open(const ttstr &path, tjs_uint32 flags) override;

    bool file_exists(const ttstr &path) override;
    bool directory_exists(const ttstr &path) override;

    tjs_int get_maxpath_length() override;
    bool get_home_directory(ttstr &result) override;
    bool get_appdata_directory(ttstr &result) override;
    bool get_savedata_directory(ttstr &result) override;

    bool path_combine(const ttstr &path1, const ttstr &path2, ttstr &result) override;

    LibRuntime::Storage::UnifiedStoragePath get_unified_storage_path(const ttstr &path) override;
    ttstr get_filesystem_path(const LibRuntime::Storage::UnifiedStoragePath &path) override;
};
