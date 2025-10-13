# ===========================================
# コンパイラ設定
# ===========================================

# C/C++標準の設定
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 出力ディレクトリの統一
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# MSVC固有の設定
if(MSVC)
    # UTF-8ソースコード対応
    add_compile_options(/utf-8)
    
    # Unicode定義
    add_compile_definitions(UNICODE _UNICODE)
    
    # 警告レベル
    add_compile_options(/W4)
    
    # マルチプロセッサコンパイル
    add_compile_options(/MP)
    
else()
    # GCC/Clang用の警告
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ビルドタイプ別の最適化
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "ビルドタイプ" FORCE)
endif()

message(STATUS "Kirikiri X Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

