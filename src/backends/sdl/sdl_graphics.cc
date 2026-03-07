#include "sdl_graphics.h"
#include <stdexcept>

using namespace Backends::SDL;
using namespace LibRuntime::Interfaces;

// --- SDLTextureHandle ---

SDLTextureHandle::SDLTextureHandle(SDL_Texture* texture, int w, int h)
    : _texture(texture), _w(w), _h(h) {}

SDLTextureHandle::~SDLTextureHandle() {
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = nullptr;
    }
}

// --- SDLGraphicsWindow ---

SDLGraphicsWindow::SDLGraphicsWindow(SDL_Window* window, SDL_Renderer* renderer)
    : _window(window), _renderer(renderer) {}

SDLGraphicsWindow::~SDLGraphicsWindow() {
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}

std::unique_ptr<ITextureHandle> SDLGraphicsWindow::create_texture(int w, int h) {
    // SDL_PIXELFORMAT_ARGB8888 = 0xAARRGGBB。吉里吉里Zの内部フォーマットと一致する
    auto* tex = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
    if (!tex) return nullptr;
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    return std::make_unique<SDLTextureHandle>(tex, w, h);
}

void SDLGraphicsWindow::update_texture(ITextureHandle* handle, const uint32_t* pixels) {
    auto* sdl = static_cast<SDLTextureHandle*>(handle);
    SDL_UpdateTexture(sdl->texture(), nullptr, pixels, sdl->width() * sizeof(uint32_t));
}

void SDLGraphicsWindow::begin_frame() {
    SDL_SetRenderTarget(_renderer, nullptr);
    SDL_RenderClear(_renderer);
}

void SDLGraphicsWindow::draw_texture(ITextureHandle* handle, const Rect& dst) {
    auto* sdl = static_cast<SDLTextureHandle*>(handle);
    SDL_Rect sdl_dst { dst.x, dst.y, dst.w, dst.h };
    SDL_RenderCopy(_renderer, sdl->texture(), nullptr, &sdl_dst);
}

void SDLGraphicsWindow::end_frame() {
    SDL_RenderPresent(_renderer);
}

void SDLGraphicsWindow::set_title(const char* title) {
    SDL_SetWindowTitle(_window, title);
}

void SDLGraphicsWindow::raise() {
    SDL_RaiseWindow(_window);
}

// --- SDLGraphicsSystem ---

void SDLGraphicsSystem::init() {
    SDL_Init(SDL_INIT_VIDEO);
}

void SDLGraphicsSystem::shutdown() {
    SDL_Quit();
}

bool SDLGraphicsSystem::poll_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return false;
    }
    return true;
}

std::unique_ptr<IGraphicsWindow> SDLGraphicsSystem::create_window(const char* title, int w, int h) {
    auto* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
    if (!window) return nullptr;
    auto* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        return nullptr;
    }
    return std::make_unique<SDLGraphicsWindow>(window, renderer);
}
