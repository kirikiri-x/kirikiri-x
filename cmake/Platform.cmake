# ===========================================
# プラットフォーム固有の設定
# ===========================================

# プラットフォーム検出
if(WIN32)
    set(PLATFORM_NAME "windows")
    
    # Windows固有の定義
    add_compile_definitions(
        UNICODE
        _UNICODE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    
    # プラットフォーム実装ターゲット
    set(PLATFORM_IMPL_TARGET win32_impl)
    
    # エントリーポイントファイル
    set(PLATFORM_ENTRY_POINT_FILES
        src/platforms/windows/main.cc
        src/platforms/windows/krkrx.rc
    )
    
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_NAME "linux")
    
    # プラットフォーム実装ターゲット
    set(PLATFORM_IMPL_TARGET linux_impl)
    
    # エントリーポイントファイル
    set(PLATFORM_ENTRY_POINT_FILES
        src/platforms/linux/main.cc
    )
    
    # Linux固有のライブラリ検索
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBADW REQUIRED IMPORTED_TARGET libadwaita-1)
    
elseif(APPLE)
    set(PLATFORM_NAME "macos")
    message(WARNING "macOS support is not implemented")
    
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# プラットフォームディレクトリの追加
message(STATUS "Platform: ${PLATFORM_NAME} (${CMAKE_BUILD_TYPE})")
add_subdirectory(src/platforms/${PLATFORM_NAME})

