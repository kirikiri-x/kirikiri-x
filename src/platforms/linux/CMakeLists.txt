# ===========================================
# KirikiriX Linux プラットフォーム実装
# ===========================================

# === Linux実装ライブラリ ===
add_library(linux_impl STATIC
    # システム機能実装
    sysfunc_impl.cpp
    sysfunc_impl.h
    
    # システムUI実装
    system_ui_impl.cc
    system_ui_impl.h
)

# エイリアスの作成
add_library(krkrx::platform::linux ALIAS linux_impl)

# === インクルードディレクトリ ===
target_include_directories(linux_impl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# === 依存ライブラリ ===
target_link_libraries(linux_impl 
    PUBLIC
        runtime             # KirikiriXランタイム
        PkgConfig::LIBADW   # GTK4/libadwaita UIライブラリ
)

# === ターゲットのプロパティ ===
set_target_properties(linux_impl PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
)