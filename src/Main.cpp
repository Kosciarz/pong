#include "Engine.hpp"

#include <print>
#include <exception>

int main() {
    try {
        pong::Engine engine;
        engine.run();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
