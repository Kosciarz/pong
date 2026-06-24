#include "Paddle.hpp"
#include "OpenGLHeaders.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

#include <array>
#include <utility>

namespace pong {

    Paddle::Paddle(const glm::vec2& position, const glm::vec2& size)
        : m_position{position},
          m_size{size},
          m_shader{SHADER_DIRECTORY / "vertex.vert", SHADER_DIRECTORY / "fragment.frag"} {
        std::array<glm::vec2, 4> vertices = {{
            {m_position.x, m_position.y},
            {m_position.x + m_size.x, m_position.y},
            {m_position.x + m_size.x, m_position.y + m_size.y},
            {m_position.x, m_position.y + m_size.y},
        }};
        std::array<unsigned int, 6> indices{0, 1, 2, 2, 3, 0};

        glCreateVertexArrays(1, &m_vao);
        glCreateBuffers(1, &m_vbo);
        glCreateBuffers(1, &m_ebo);

        glNamedBufferData(
            m_vbo, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);
        glNamedBufferData(
            m_ebo, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(glm::vec2));
        glVertexArrayElementBuffer(m_vao, m_ebo);

        glEnableVertexArrayAttrib(m_vao, 0);
        glVertexArrayAttribFormat(m_vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vao, 0, 0);
    }

    Paddle::~Paddle() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    Paddle::Paddle(Paddle&& other) noexcept
        : m_position{std::move(other.m_position)},
          m_size{std::move(other.m_size)},
          m_vao{std::exchange(other.m_vao, 0)},
          m_vbo{std::exchange(other.m_vbo, 0)},
          m_ebo{std::exchange(other.m_ebo, 0)},
          m_shader{std::move(other.m_shader)} {}

    Paddle& Paddle::operator=(Paddle&& other) noexcept {
        if (this != &other) {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(1, &m_vbo);
            glDeleteBuffers(1, &m_ebo);

            m_position = std::move(other.m_position);
            m_size = std::move(other.m_size);
            m_vao = std::exchange(other.m_vao, 0);
            m_vbo = std::exchange(other.m_vbo, 0);
            m_ebo = std::exchange(other.m_ebo, 0);
            m_shader = std::move(other.m_shader);
        }

        return *this;
    }

    void Paddle::update(const float dt) {}

    void Paddle::render() const {
        m_shader.use();
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

} // namespace pong
