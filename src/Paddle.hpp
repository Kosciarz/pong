#pragma once

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

#include <array>

namespace pong {

    class Paddle {
    public:
        Paddle(const glm::vec2& position, const glm::vec2& size);
        ~Paddle();

        Paddle(const Paddle&) = delete;
        Paddle& operator=(const Paddle&) = delete;

        Paddle(Paddle&& other) noexcept;
        Paddle& operator=(Paddle&& other) noexcept;

        void update(const float dt);
        void render() const;

    private:
        glm::vec2 m_position;
        glm::vec2 m_size;

        GLuint m_vao, m_vbo, m_ebo;
        Shader m_shader;
    };

} // namespace pong
