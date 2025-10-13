# ===========================================
# KirikiriX Windows プラットフォーム実装
# ===========================================

# === Windows実装ライブラリ ===
add_library(win32_impl STATIC
    # コンソール実装
    console_impl.cc
    console_impl.h
    
    # ファイルシステム実装
    filesystem_impl.cc
    filesystem_impl.h
    localfile_stream.cpp
    localfile_stream.h
    
    # システムUI実装
    system_ui_impl.cc
    system_ui_impl.h
    
    # システム機能実装
    sysfunc_impl.cc
    sysfunc_impl.h
    
    # 環境変数実装
    environment_impl.cc
    environment_impl.h
)

# エイリアスの作成
add_library(krkrx::platform::windows ALIAS win32_impl)

# === コンパイル定義 ===
target_compile_definitions(win32_impl
    PRIVATE
        UNICODE
        _UNICODE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        $<$<CXX_COMPILER_ID:MSVC>:IS_MSVC=1>
)

# === インクルードディレクトリ ===
target_include_directories(win32_impl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# === 依存ライブラリ ===
target_link_libraries(win32_impl 
    PUBLIC
        runtime             # KirikiriXランタイム
    PRIVATE
        # Windows システムライブラリ
        pathcch             # パス操作API (PathCchCombine等)
        rpcrt4              # GUID生成用RPC API
        comctl32            # コモンコントロール
)

# === ターゲットのプロパティ ===
set_target_properties(win32_impl PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)