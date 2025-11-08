#pragma once
#include <tjs.h>
#include <tjsError.h>

namespace LibRuntime {
    class ScriptManager {
    public:
        /**
         * スクリプトマネージャーの初期化を行います。
         * @param startup_script_name スタートアップとして動かすスクリプト名
         * @param encoding 文字エンコーディング
         * @param krkr_compatible 吉里吉里互換モード (0: none, 1: krkrz, 2: krkr2)
         * @return 初期化が成功したかどうか (初期化済みの場合は初期化せずに true が返されます)
         */
        static bool init(const ttstr& startup_script_name, const ttstr& encoding, int krkr_compatible);
        static void run(const ttstr& script);
        static tTJSVariant eval(const ttstr& script);
        static bool assign_message(const ttstr& msg, const ttstr& val);
        static bool handle_script_error(eTJSScriptException &error);
        static ttstr get_script_engine_version();

    private:
        static bool debug_mode;
        static ttstr file_encoding;
        static tTJS *tjs_engine;
        static bool initialized;
        static ttstr startup_script_name;
    };
}
