#include "Ball.hpp"
#include "Game.hpp"

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace pong {

    Ball::Ball(const glm::vec2& position,
               const float radius,
               const glm::vec2& velocity,
               const BallType type)
        : m_position{position},
          m_radius{radius},
          m_velocity{velocity},
          m_type{type} {}

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
    }

} // namespace pong
