#pragma once

#include "OpenGLHeaders.hpp"

namespace pong {

    struct InputState {
        // keys
        bool key_w = false;
        bool key_s = false;
        bool key_a = false;
        bool key_d = false;

        bool key_up = false;
        bool key_down = false;
        bool key_left = false;
        bool key_right = false;
    };

    class InputHandler {
    public:
        void update(GLFWwindow* window);

        [[nodiscard]] const InputState& state() const { return m_state; }

    private:
        InputState m_state;
    };

} // namespace pong

