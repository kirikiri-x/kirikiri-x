# ===========================================
# KirikiriX Linux プラットフォーム実装
# ===========================================

# === Linux実装ライブラリ ===
add_library(macos_impl STATIC
    # システム機能実装
    sysfunc_impl.cpp
    sysfunc_impl.h
)

# エイリアスの作成
add_library(krkrx::platform::macos ALIAS macos_impl)

# === インクルードディレクトリ ===
target_include_directories(macos_impl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# === 依存ライブラリ ===
target_link_libraries(macos_impl
    PUBLIC
        runtime             # KirikiriXランタイム
)

# === ターゲットのプロパティ ===
set_target_properties(macos_impl PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
)