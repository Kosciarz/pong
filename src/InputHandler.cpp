#include "InputHandler.hpp"
#include "OpenGLHeaders.hpp"

namespace pong {

    void InputHandler::update(GLFWwindow* window) {
        m_state.key_w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        m_state.key_s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

        m_state.key_up = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
        m_state.key_down = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
    }

} // namespace pong
