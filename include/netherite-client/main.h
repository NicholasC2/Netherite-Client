#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>

namespace netherite {

struct ClientConfig {
    std::string version = "1.20.4";
    bool enableLogging = true;
    bool enableMultithreading = false;
};

class MinecraftClient {
public:
    MinecraftClient() = default;
    ~MinecraftClient() = default;

    bool init(const ClientConfig& config = ClientConfig()) {
        this->config = config;
        
        if(this->config.enableLogging) { 
            std::cout << "[Netherite] Initialized with version: " << config.version << "\n";
        }
        initialized = true;
        return true;
    }

    bool connectToServer(const std::string& host, uint16_t port, const std::string& username) {
        if (!initialized) {
            if(this->config.enableLogging) {
                std::cerr << "[Netherite] Cannot connect before initialization.\n";
            }
            return false;
        }

        if(this->config.enableLogging) {
            std::cout << "[Netherite] Connecting to " << host << ":" << port << " as " << username << "\n";
        }

        

        connected = true;
        return true;
    }

    bool isConnected() const {
        return connected;
    }

    void tick() {
        if (!connected) return;
    }

    void shutdown() {
        connected = false;
        if(this->config.enableLogging) {
            std::cout << "[Netherite] Client shutdown.\n";
        }
    }

    std::string getServerVersion() const {
        return config.version;
    }

private:
    bool initialized = false;
    bool connected = false;

    ClientConfig config;
};

} // namespace netherite
