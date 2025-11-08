#pragma once
#include <tjs.h>

namespace LibRuntime::Storage {
    class UnifiedStoragePath {
    public:
        UnifiedStoragePath(const ttstr &media_name, const ttstr &domain_name, const ttstr &path);
        ~UnifiedStoragePath();

        [[nodiscard]] ttstr get_media_name() const;
        [[nodiscard]] ttstr get_domain_name() const;
        [[nodiscard]] ttstr get_path() const;

        void set_media_name(const ttstr &media_name);
        void set_domain_name(const ttstr &domain_name);
        void set_path(const ttstr &path);

        [[nodiscard]] ttstr get_fullpath() const;

        // ユーティリティ
        [[nodiscard]] UnifiedStoragePath parent_directory() const;
        [[nodiscard]] ttstr filename() const;
        [[nodiscard]] ttstr extension() const;

        explicit operator ttstr() const {
            return get_fullpath();
        }

        operator tjs_string() const {
            return get_fullpath().AsStdString();
        }

    private:
        ttstr media_name;
        ttstr domain_name;
        ttstr path;
    };
}
