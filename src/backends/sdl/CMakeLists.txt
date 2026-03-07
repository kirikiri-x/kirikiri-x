# ===========================================
# SDL2 グラフィックスバックエンド
# ===========================================
add_library(sdl_backend STATIC
    sdl_graphics.cc
)

add_library(krkrx::sdl_backend ALIAS sdl_backend)

target_include_directories(sdl_backend
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        # runtime の interfaces/ を参照できるようにする
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/runtime/core>
)

target_link_libraries(sdl_backend
    PUBLIC
        SDL2::SDL2-static
)

set_target_properties(sdl_backend PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
