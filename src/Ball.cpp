#include "Ball.hpp"
#include "OpenGLHeaders.hpp"
#include "Game.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>
#include <numbers>

namespace pong {

    Ball::Ball(const glm::vec2& position,
               const float radius,
               const glm::vec2& velocity,
               const BallType type)
        : m_position{position},
          m_radius{radius},
          m_velocity{velocity},
          m_type{type},
          m_shader{SHADER_DIRECTORY / "vertex.vert", SHADER_DIRECTORY / "fragment.frag"} {
        constexpr auto segments = 100;

        std::vector<float> vertices;
        vertices.reserve((segments + 2) * 2);
        vertices.push_back(0.0f);
        vertices.push_back(0.0f);

        for (int i = 0; i < segments; ++i) {
            const float theta = 2.0f * std::numbers::pi_v<float> * i / segments;

            vertices.push_back(m_radius * std::cos(theta));
            vertices.push_back(m_radius * std::sin(theta));
        }

        vertices.push_back(m_position.x + m_radius);
        vertices.push_back(m_position.y);

        glCreateVertexArrays(1, &m_vao);
        glCreateBuffers(1, &m_vbo);

        glNamedBufferData(m_vbo, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(glm::vec2));

        glEnableVertexArrayAttrib(m_vao, 0);
        glVertexArrayAttribFormat(m_vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vao, 0, 0);

        m_vertex_count = vertices.size() / 2;
    }

    Ball::~Ball() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    Ball::Ball(Ball&& other) noexcept
        : m_position{std::move(other.m_position)},
          m_radius{std::move(other.m_radius)},
          m_vao{std::exchange(other.m_vao, 0)},
          m_vbo{std::exchange(other.m_vbo, 0)},
          m_shader{std::move(other.m_shader)} {}

    Ball& Ball::operator=(Ball&& other) noexcept {
        if (this != &other) {
            glDeleteVertexArrays(1, &m_vao);
            glDeleteBuffers(1, &m_vbo);

            m_position = std::move(other.m_position);
            m_radius = std::move(other.m_radius);
            m_vao = std::exchange(other.m_vao, 0);
            m_vbo = std::exchange(other.m_vbo, 0);
            m_shader = std::move(other.m_shader);
        }

        return *this;
    }

    void Ball::update(const GameContext& ctx) {
        m_position += m_velocity * ctx.delta_time;

        switch (m_type) {
        case BallType::TwoPlayer: {
            if (m_position.y + m_radius >= 1.0f || m_position.y - m_radius <= -1.0f) {
                m_velocity.y *= -1.0f;
            }
            break;
        }
        case BallType::SinglePlayer: {
            if (m_position.y + m_radius >= 1.0f) {
                m_velocity.y *= -1.0f;
            }
            if (m_position.x + m_radius >= 1.0f * ctx.aspect_ratio ||
                m_position.x - m_radius <= -1.0f * ctx.aspect_ratio) {
                m_velocity.x *= -1.0f;
            }
            break;
        }
        }

        const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{m_position, 0.0f});
        const glm::mat4 projection = glm::ortho(-ctx.aspect_ratio, ctx.aspect_ratio, -1.0f, 1.0f);

        m_shader.use();
        glUniformMatrix4fv(m_shader.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(
            m_shader.uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }

    void Ball::render() {
        m_shader.use();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertex_count);
    }

} // namespace pong
