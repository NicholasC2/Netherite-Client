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

        bool quit;
        SDL_Event event;

        float x = 0;
        float y = 0;
        float xv = 0;
        float yv = 0;

        while(!quit) {
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }
            
            yv+=0.001;
            x+=xv;
            y+=yv;

            if(y > 375) {
                y = 375;
                yv = 0-yv/2;
            }

            SDL_SetWindowPosition(window,x,y);
        }
    }

    return 0;
}