#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>

namespace netherite {

struct Packet {
    int length;
    int id;
    unsigned char* data;
};

class PacketWrangler {
public:
    bool init() {
        initialized = true;
        return true;
    }

    void sendPacket(const Packet& packet) {
        if (!initialized) {
            return;
        }

        
    }

    void connect(const std::string& host, uint16_t port) {
        if (!initialized) {
            return;
        }

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            return;
        }
    }

    void disconnect() {
        if (!initialized) {
            return;
        }

        
    }

private:
    bool initialized = false;
};

} // namespace netherite
