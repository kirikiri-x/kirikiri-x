#pragma once
#include <SDL.h>
#include "interfaces/graphics.h"

namespace Backends::SDL {

    class SDLTextureHandle : public LibRuntime::Interfaces::ITextureHandle {
    public:
        SDLTextureHandle(SDL_Texture* texture, int w, int h);
        ~SDLTextureHandle() override;

        int width() const override  { return _w; }
        int height() const override { return _h; }

        SDL_Texture* texture() const { return _texture; }

    private:
        SDL_Texture* _texture;
        int _w, _h;
    };

    class SDLGraphicsWindow : public LibRuntime::Interfaces::IGraphicsWindow {
    public:
        SDLGraphicsWindow(SDL_Window* window, SDL_Renderer* renderer);
        ~SDLGraphicsWindow() override;

        std::unique_ptr<LibRuntime::Interfaces::ITextureHandle> create_texture(int w, int h) override;
        void update_texture(LibRuntime::Interfaces::ITextureHandle* handle, const uint32_t* pixels) override;

        void begin_frame() override;
        void draw_texture(LibRuntime::Interfaces::ITextureHandle* handle, const LibRuntime::Interfaces::Rect& dst) override;
        void end_frame() override;

        void set_title(const char* title) override;
        void raise() override;

    private:
        SDL_Window*   _window;
        SDL_Renderer* _renderer;
    };

    class SDLGraphicsSystem : public LibRuntime::Interfaces::IGraphicsSystem {
    public:
        void init() override;
        void shutdown() override;
        bool poll_events() override;
        std::unique_ptr<LibRuntime::Interfaces::IGraphicsWindow> create_window(const char* title, int w, int h) override;
    };

} // namespace Backends::SDL
