#define SDL_MAIN_HANDLED
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <sstream>

using namespace std;

int version[] = {1,8,9};
std::string versionString = "1.8.9";

bool initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) != true) {
        std::string message = "SDL Failed to Initialize: ";
        message += SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.c_str(), NULL);
        SDL_Quit();
        return false;
    } else {
        return true;
    }
}

SDL_Window* createWindow(const char* title, int w, int h, SDL_WindowFlags flags) {
    SDL_Window *window = SDL_CreateWindow(title, w, h, flags);

    if(window == NULL) {
        std::string message = "SDL Window Creation Failed: ";
        message += SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.c_str(), NULL);
        SDL_Quit();
        return NULL;
    } else {
        return window;
    }
}

void startMainLoop(SDL_Window* window) {
    SDL_Event event;
    bool quit;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        
    }
}

VkInstance instance;
void createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Netherite Client";
    appInfo.applicationVersion = VK_MAKE_VERSION(version[0], version[1], version[2]);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if(result != VK_SUCCESS) {
        std::string message = "VULKAN Instance Creation Failed: ";
        message += result;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "VULKAN Error!", message.c_str(), NULL);
        SDL_Quit(); 
    }
}

void initVulkan() {
    createInstance();
}

void cleanup(SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char ** argv) {
    if(!initSDL()) return 1;

    std::string window_title = "Netherite Client - " + versionString;

    SDL_Window* window = createWindow(window_title.c_str(), 640, 360, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    if(!window) {
        return 2;
    } else {
        SDL_SetWindowAspectRatio(window, 1.77777777778, 1.77777777778);
        startMainLoop(window);
    }

    cleanup(window);
    return 0;
}