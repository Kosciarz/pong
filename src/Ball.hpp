#pragma once

#include "Paddle.hpp"

#include <glm/glm.hpp>

namespace pong {

    struct GameContext;

    enum class BallType { TwoPlayer, SinglePlayer };

    class Ball {
    public:
        Ball(const glm::vec2& position,
             const float radius,
             const glm::vec2& velocity,
             const BallType type);

        void update(const GameContext& ctx);
        void handle_collision(const PaddleType side);

        [[nodiscard]] const glm::vec2& position() const { return m_position; }
        [[nodiscard]] float radius() const { return m_radius; }
        [[nodiscard]] const glm::vec2& velocity() const { return m_velocity; }
        [[nodiscard]] BallType type() const { return m_type; }

        void set_position(const glm::vec2& pos) { m_position = pos; };
        void set_velocity(const glm::vec2& vel) { m_velocity = vel; }

    private:
        glm::vec2 m_position;
        float m_radius;
        glm::vec2 m_velocity;
        BallType m_type;
    };

} // namespace pong
