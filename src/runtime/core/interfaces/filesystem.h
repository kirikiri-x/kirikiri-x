#pragma once
#include "tjs.h"
#include "tjsTypes.h"
#include "../storage/unified_storage_path.h"

namespace LibRuntime::Interfaces {
    /**
     * ファイルシステムへアクセスするためのインターフェース
     */
    class IFileSystem {
    public:
        // カレントディレクトリ
        virtual size_t get_current_directory(ttstr &result) = 0;
        virtual bool set_current_directory(const ttstr &path) = 0;

        // ファイル開閉
        virtual tTJSBinaryStream *open(const ttstr &path, tjs_uint32 flags) = 0;

        // 存在確認
        virtual bool file_exists(const ttstr &path) = 0;
        virtual bool directory_exists(const ttstr &path) = 0;

        // ファイルシステム情報関連
        virtual tjs_int get_maxpath_length() = 0;
        virtual bool get_home_directory(ttstr &result) = 0;
        virtual bool get_appdata_directory(ttstr &result) = 0;
        virtual bool get_savedata_directory(ttstr &result) = 0;

        // ユーティリティ
        virtual bool path_combine(const ttstr &path1, const ttstr &path2, ttstr &result) = 0;

        // ユニファイドストレージパス
        virtual LibRuntime::Storage::UnifiedStoragePath get_unified_storage_path(const ttstr &path) = 0;
        virtual ttstr get_filesystem_path(const LibRuntime::Storage::UnifiedStoragePath &path) = 0;
    };

    /**
     * IFileSystem のフォールバック実装
     */
    class FileSystemFallbackImpl : public IFileSystem {
    public:
        size_t get_current_directory(ttstr &result) override {
            return -1;
        };
        bool set_current_directory(const ttstr &path) override {
            return false;
        };

        bool file_exists(const ttstr &path) override {
            return false;
        }

        bool directory_exists(const ttstr &path) override {
            return false;
        }

        tTJSBinaryStream *open(const ttstr &path, tjs_uint32 flags) override {
            return nullptr;
        };

        tjs_int get_maxpath_length() override {
            return 260;
        };

        bool get_home_directory(ttstr &result) override {
            return false;
        }

        bool get_appdata_directory(ttstr &result) override {
            return false;
        }

        bool get_savedata_directory(ttstr &result) override {
            return false;
        }

        bool path_combine(const ttstr &path1, const ttstr &path2, ttstr &result) override {
            return false;
        }

        LibRuntime::Storage::UnifiedStoragePath get_unified_storage_path(const ttstr &path) override {
            return LibRuntime::Storage::UnifiedStoragePath(TJS_W(""), TJS_W(""), path);
        }
        
        ttstr get_filesystem_path(const LibRuntime::Storage::UnifiedStoragePath &path) override {
            return ttstr(path.get_fullpath().c_str());
        }
        
    };
}

