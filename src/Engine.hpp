#pragma once

#include "OpenGLHeaders.hpp"

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
    };

} // namespace pong
