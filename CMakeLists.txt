# ===========================================
# 吉里吉里X (KirikiriX)
# Cross-platform game engine based on Kirikiri Z
# ===========================================

cmake_minimum_required(VERSION 3.21)
project(krkrx 
    VERSION 0.1.0
    DESCRIPTION "マルチプラットフォーム対応吉里吉里Zランタイム"
    LANGUAGES C CXX
)

# CMakeモジュールパスの追加
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# === 設定の読み込み ===
include(CompilerSettings)
include(Dependencies)

# === サードパーティライブラリ ===
add_subdirectory(src/third_party/oniguruma)

# === インターフェース層 ===
add_library(platform_interface INTERFACE)
target_include_directories(platform_interface INTERFACE
    src/runtime/core/interfaces
)

# === ランタイム層 ===
add_subdirectory(src/runtime)

# === プラットフォーム実装 ===
include(Platform)

# === メイン実行ファイル ===
add_executable(${PROJECT_NAME} 
    ${PLATFORM_ENTRY_POINT_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PLATFORM_IMPL_TARGET}
    runtime
)

# 実行ファイルの設定
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "krkrx"
    DEBUG_POSTFIX "_d"
)

# === テスト ===
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(src/tests)
    endif()
endif()

# === ビルド情報の表示 ===
message(STATUS "=== KIRIKIRI X BUILD INFORMATION ==========")
message(STATUS "PROJECT: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "PLATFORM: ${PLATFORM_NAME}")
message(STATUS "BUILD TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "===========================================")