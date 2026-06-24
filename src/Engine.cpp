#include "Engine.hpp"
#include "OpenGLHeaders.hpp"
#include "OpenGLDebugCallback.hpp"

#include <stdexcept>
#include <print>

namespace {

    void error_callback(const int error, const char* desc) {
        std::println("Error ({}): {}", error, desc);
    }

} // namespace

namespace pong {

    Engine::Engine()
        : m_window_width{WINDOW_WIDTH},
          m_window_height{WINDOW_HEIGHT},
          m_last_time{glfwGetTime()} {
        if (!glfwInit()) {
            throw std::runtime_error{"failed to init GLFW"};
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        m_window = glfwCreateWindow(m_window_width, m_window_height, "Pong", nullptr, nullptr);
        if (!m_window) {
            throw std::runtime_error{"failed to create window"};
        }

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGL(glfwGetProcAddress)) {
            throw std::runtime_error{"failed to init GLAD"};
        }

        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, Engine::framebuffer_size_callback);
        glfwSetKeyCallback(m_window, Engine::key_callback);

        glViewport(0, 0, m_window_width, m_window_height);

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(pong::gl_debug_callback, nullptr);
        }

        m_game.emplace();
    }

    Engine::~Engine() {
        m_game.reset();

        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        glfwTerminate();
    }

    void Engine::run() {
        while (!glfwWindowShouldClose(m_window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

            glfwPollEvents();
            m_input_handler.update(m_window);

            const double current_time = glfwGetTime();
            const float dt = static_cast<float>(current_time - m_last_time);
            m_last_time = current_time;

            const float aspect_ratio =
                static_cast<float>(m_window_width) / static_cast<float>(m_window_height);

            const GameContext ctx = {.delta_time = dt,
                                     .aspect_ratio = aspect_ratio,
                                     .input_state = m_input_handler.state()};

            m_game->update(ctx);
            m_game->render();

            glfwSwapBuffers(m_window);
        }
    }
    void Engine::framebuffer_size_callback(GLFWwindow* window, const int width, const int height) {
        glViewport(0, 0, width, height);

        auto* e = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        if (e) {
            e->m_window_width = width;
            e->m_window_height = height;
        }
    }
    void Engine::key_callback(
        GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

} // namespace pong
