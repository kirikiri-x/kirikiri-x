# ===========================================
# 外部依存関係の管理
# ===========================================

include(FetchContent)

# FetchContent の共通設定
set(FETCHCONTENT_QUIET OFF)

# -----------------------------
# SDL2（描画・入力の共通基盤）
# -----------------------------
FetchContent_Declare(
    sdl2
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.32.4.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

# SDL2のオプション設定
set(SDL2_DISABLE_INSTALL ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

# -----------------------------
# Google Test
# -----------------------------
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

# Google Test のオプション設定
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

# -----------------------------
# 依存関係の有効化
# -----------------------------
FetchContent_MakeAvailable(sdl2 googletest)

# エイリアスの作成（統一的なターゲット名）
if(NOT TARGET SDL2::SDL2)
    add_library(SDL2::SDL2 ALIAS SDL2-static)
endif()

message(STATUS "All dependencies have been retrieved")

