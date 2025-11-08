#include "filesystem_impl.h"
#include "localfile_stream.h"
#include <windows.h>
#include <pathcch.h>
#include <ShlObj.h>
#include <algorithm>
#include <cwctype>

using namespace LibRuntime::Storage;

size_t WindowsFileSystem::get_current_directory(ttstr &result) {
    DWORD buflen = GetCurrentDirectoryW(0, nullptr);
    if (buflen == 0) {
        result.Clear();
        return 0;
    }
    auto *buf = new tjs_char[buflen + 1];
    DWORD written = GetCurrentDirectoryW(buflen, reinterpret_cast<LPWSTR>(buf));
    result = ttstr(buf);
    delete[] buf;
    return written;
}

bool WindowsFileSystem::set_current_directory(const ttstr &path) {
    BOOL result = SetCurrentDirectoryW(reinterpret_cast<LPCWSTR>(path.c_str()));
    return (bool)result;
}

tTJSBinaryStream *WindowsFileSystem::open(const ttstr &path, tjs_uint32 flags) {
    return new WindowsLocalFileStream(path, flags);
}

bool WindowsFileSystem::file_exists(const ttstr &path) {
    DWORD attr = GetFileAttributesW((LPCWSTR)path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

bool WindowsFileSystem::directory_exists(const ttstr &path) {
    DWORD attr = GetFileAttributesW((LPCWSTR)path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
}

tjs_int WindowsFileSystem::get_maxpath_length() {
    return MAX_PATH;
}

bool WindowsFileSystem::get_home_directory(ttstr &result) {
    PWSTR path = nullptr;
    if (HRESULT hr = SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &path); hr != S_OK) {
        result.Clear();
        return false;
    }

    result = ttstr(path);

    CoTaskMemFree(path);
    return true;
}

bool WindowsFileSystem::get_appdata_directory(ttstr &result) {
    PWSTR path = nullptr;
    if (const HRESULT hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path); hr != S_OK) {
        result.Clear();
        return false;
    }

    result = ttstr(path);

    CoTaskMemFree(path);
    return true;
}

bool WindowsFileSystem::get_savedata_directory(ttstr &result) {
    ttstr current_dir;
    if (get_current_directory(current_dir) == 0) {
        result.Clear();
        return false;
    }

    ttstr combined_path;
    if (!path_combine(current_dir, TJS_W("savedata"), combined_path)) {
        result.Clear();
        return false;
    }

    result = combined_path;
    return true;
}


bool WindowsFileSystem::path_combine(const ttstr &path1, const ttstr &path2, ttstr &result) {
    tjs_char combined_path[MAX_PATH];
    HRESULT hr = PathCchCombine((PWSTR)combined_path, MAX_PATH, (PCWSTR)path1.c_str(), (PCWSTR)path2.c_str());
    if (hr != S_OK) {
        result.Clear();
        return false;
    }

    result = ttstr(combined_path);
    return true;
}

UnifiedStoragePath WindowsFileSystem::get_unified_storage_path(const ttstr &path) {
    // path には Windows ファイルシステムで有効なパスが入っている．これを統合ストレージ名に変換する

    // パスを正規化する
    tjs_char normalized_path[MAX_PATH];
    if (PathCchCanonicalize((PWSTR)normalized_path, MAX_PATH, (PCWSTR)path.c_str()) != S_OK) {
        return UnifiedStoragePath(TJS_W(""), TJS_W(""), path);
    }

    // ドライブ文字を取得 (例: C:\path -> c)
    ttstr drive;
    if (normalized_path[1] == L':') {
        drive = ttstr(normalized_path[0]);
        drive = drive.AsLowerCase();
    } else {
        drive = ttstr();
    }

    // パスからドライブ部分を除去してスラッシュに変換 (例: C:\path -> /path)
    ttstr path_part = normalized_path;
    if (path_part.length() >= 2 && path_part[1] == L':') {
        path_part = path_part + 2;
    }
    path_part.Replace(TJS_W("\\"), TJS_W("/"));

    drive += path_part;
    
    return UnifiedStoragePath(TJS_W("file"), TJS_W("."), drive);
}

ttstr WindowsFileSystem::get_filesystem_path(const UnifiedStoragePath &path) {
    // path には 統合ストレージパスが入っている．これを Windows ファイルシステムのパスに変換する
    // ドライブ文字を取得 (例: c: -> C:\)
    ttstr drive;
    if (path.get_media_name() == TJS_W("file")) {
        drive = path.get_path()[0];
    } else {
        drive = TJS_W("");
    }

    // パスを結合する
    ttstr path_part = path.get_path().c_str();
    if (path_part.length() >= 2 && path_part[1] == L'/') {
        path_part = path_part + 2;
    }
    path_part.Replace(TJS_W("/"), TJS_W("\\"));

    // Windows API でノーマライズする
    tjs_char normalized_path[MAX_PATH];
    if (PathCchCanonicalize((PWSTR)normalized_path, MAX_PATH, (PCWSTR)path.get_fullpath().c_str()) != S_OK) {
        return ttstr();
    }
    
    return ttstr(normalized_path);
}

