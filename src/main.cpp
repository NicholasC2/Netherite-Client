#define SDL_MAIN_HANDLED
#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <netherite-client/main.h>
#include <thread>
#include <chrono>
#include <string>

using namespace netherite;

int version[] = {1,8,9};
std::string versionString = "1.8.9";

bool initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::string message = "SDL Failed to Initialize: ";
        message += SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.c_str(), NULL);
        SDL_Quit();
        return false;
    }
    return true;
}

SDL_Window* createWindow(const char* title, int w, int h, SDL_WindowFlags flags) {
    SDL_Window *window = SDL_CreateWindow(title, w, h, flags);
    if(window == NULL) {
        std::string message = "SDL Window Creation Failed: ";
        message += SDL_GetError();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error!", message.c_str(), NULL);
        SDL_Quit();
        return NULL;
    }
    return window;
}

void startMainLoop(SDL_Window* window) {
    SDL_Event event;
    bool quit = false;
    while(!quit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        // TODO: render here or tick client
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
        message += std::to_string(result);
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
    }

    SDL_SetWindowAspectRatio(window, 1.77777777778, 1.77777777778);

    // Initialize Vulkan
    initVulkan();

    std::cout << "=== Netherite Client ===\n";

    MinecraftClient client;

    // Initialize the client
    ClientConfig config;
    config.version = "1.20.4";
    config.enableLogging = true;

    if (!client.init(config)) {
        std::cerr << "Failed to initialize Netherite client.\n";
        cleanup(window);
        return 1;
    }

    // Connect to a Minecraft server
    std::string host = "localhost";
    uint16_t port = 25565; 
    std::string username = "Steve";

    if (!client.connectToServer(host, port, username)) {
        std::cerr << "Failed to connect to server.\n";
        cleanup(window);
        return 1;
    }

    // Main game loop
    while (client.isConnected()) {
        client.tick();

        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_EVENT_QUIT) {
                client.shutdown();
            }
        }
    }

    client.shutdown();
    std::cout << "Disconnected.\n";

    cleanup(window);

    return 0;
}
