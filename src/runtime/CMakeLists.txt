# ===========================================
# KirikiriX ランタイムライブラリ
# ===========================================

# === ソースファイルの収集 ===
# TJS2スクリプトエンジン（変更が少ないため、GLOBを使用）
file(GLOB_RECURSE TJS2_SOURCES 
    CONFIGURE_DEPENDS
    tjs2/*.cpp
)
list(REMOVE_ITEM TJS2_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/tjs2/tjsDateWordMap.cc
)

# コアエンジン
file(GLOB_RECURSE CORE_SOURCES 
    CONFIGURE_DEPENDS
    core/*.cc
)

# === ランタイムライブラリの定義 ===
add_library(runtime STATIC
    ${TJS2_SOURCES}
    ${CORE_SOURCES}
)

# ライブラリのエイリアス（モダンな参照方法）
add_library(krkrx::runtime ALIAS runtime)

# === インクルードディレクトリ ===
target_include_directories(runtime
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/core>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tjs2>
        $<INSTALL_INTERFACE:include>
)

# === 依存ライブラリ ===
# SDL2mainの依存関係（必要な場合のみ）
if(TARGET SDL2::SDL2main)
    target_link_libraries(runtime PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(runtime 
    PUBLIC
        onig                # 正規表現エンジン
        SDL2::SDL2-static   # マルチメディア機能
)

# === ターゲットのプロパティ ===
set_target_properties(runtime PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON
)

# デバッグビルド時のログ出力
if(CMAKE_BUILD_TYPE MATCHES Debug)
    list(LENGTH TJS2_SOURCES TJS2_COUNT)
    list(LENGTH CORE_SOURCES CORE_COUNT)
    message(STATUS "Runtime TJS2ソース数: ${TJS2_COUNT}")
    message(STATUS "Runtime Coreソース数: ${CORE_COUNT}")
endif()