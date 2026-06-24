#pragma once

#include "Game.hpp"
#include "OpenGLHeaders.hpp"
#include "InputHandler.hpp"

#include <optional>

namespace pong {

    inline static constexpr auto WINDOW_WIDTH = 1080;
    inline static constexpr auto WINDOW_HEIGHT = 720;

    class Engine {
    public:
        Engine();
        ~Engine();

        void run();

    private:
        static void framebuffer_size_callback(GLFWwindow* window,
                                              const int width,
                                              const int height);
        static void key_callback(GLFWwindow* window,
                                 const int key,
                                 const int scancode,
                                 const int action,
                                 const int mods);

    private:
        GLFWwindow* m_window;

        int m_window_width;
        int m_window_height;

        double m_last_time = 0.0f;

        InputHandler m_input_handler;

        std::optional<Game> m_game;
    };

} // namespace pong
