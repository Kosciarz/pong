#pragma once

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

namespace pong {

    struct GameContext;

    class Ball {
    public:
        Ball(const glm::vec2& position, const float radius);
        ~Ball();

        Ball(const Ball&) = delete;
        Ball& operator=(const Ball&) = delete;

        Ball(Ball&& other) noexcept;
        Ball& operator=(Ball&& other) noexcept;

        void update(const GameContext& ctx);
        void render();

    private:
        glm::vec2 m_position;
        float m_radius;
        glm::vec2 m_velocity;

        GLuint m_vao, m_vbo;
        Shader m_shader;
        std::size_t m_vertex_count;
    };

} // namespace pong
