#pragma once

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

#include <array>

namespace pong {

    struct GameContext;

    enum class PaddleType { Left, Right };

    class Paddle {
    public:
        Paddle(const glm::vec2& position, const glm::vec2& size, const PaddleType type);
        ~Paddle();

        Paddle(const Paddle&) = delete;
        Paddle& operator=(const Paddle&) = delete;

        Paddle(Paddle&& other) noexcept;
        Paddle& operator=(Paddle&& other) noexcept;

        void update(const GameContext& ctx);
        void render() const;

        [[nodiscard]] const glm::vec2& position() const { return m_position; }
        [[nodiscard]] const glm::vec2& size() const { return m_size; }
        [[nodiscard]] PaddleType type() const { return m_type; }

        void set_position(const glm::vec2& pos) { m_position = pos; }
        void set_size(const glm::vec2& size) { m_size = size; }

    private:
        glm::vec2 m_position;
        glm::vec2 m_size;
        PaddleType m_type;

        GLuint m_vao, m_vbo, m_ebo;
        Shader m_shader;
    };

} // namespace pong
