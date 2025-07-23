#define SDL_MAIN_HANDLED
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char ** argv) {
    if(SDL_Init(SDL_INIT_VIDEO) != true) {
        std::ostringstream message;
        std::string message_prefix = "SDL Failed to Initialize: ";
        message << message_prefix << SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.str().c_str(), NULL);
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Minecraft - 1.8.9", 640, 360, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(window == NULL) {
        std::ostringstream message;
        std::string message_prefix = "SDL Window Creation Failed: " ;
        message << message_prefix << SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.str().c_str(), NULL);
        return 2;
    } else {
        SDL_SetWindowAspectRatio(window, 1.77777777778, 1.77777777778);

        SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
        if(renderer == NULL) {
            std::ostringstream message;
            std::string message_prefix = "SDL Renderer Creation Failed: " ;
            message << message_prefix << SDL_GetError();
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.str().c_str(), NULL);
            return 3;
        }

        SDL_Surface *logo = SDL_LoadBMP("assets/mojangstudios.bmp");
        if (!logo) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", SDL_GetError(), NULL);
        }
        SDL_Texture *logo_texture = SDL_CreateTextureFromSurface(renderer, logo);

        bool quit;
        SDL_Event event;
        while(!quit) {
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }
            SDL_SetRenderDrawColor(renderer, 223, 29, 63, 255);

            SDL_RenderClear(renderer);

            SDL_FRect logo_rect = {0, 0, 1024, 256};

            int w;
            int h;

            SDL_GetWindowSize(window, &w, &h);

            SDL_FRect screen_logo_rect = {(w - 1024 * w/1.5/1024) / 2, (h - 256 * w/1.5/1024) / 2.5, 1024 * w/1.5/1024, 256 * w/1.5/1024};

            SDL_RenderTexture(renderer, logo_texture, &logo_rect, &screen_logo_rect);

            SDL_RenderPresent(renderer);
        }
    }

    return 0;
}