#include "Paddle.hpp"
#include "Game.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <utility>
#include <algorithm>

namespace pong {

    Paddle::Paddle(const glm::vec2& position, const glm::vec2& size, const PaddleType type)
        : m_position{position},
          m_size{size},
          m_type{type} {}

    void Paddle::update(const GameContext& ctx) {
        constexpr auto speed = 0.2f;

        switch (m_type) {
        case PaddleType::Left: {
            if (ctx.input_state.key_w) {
                m_position.y += speed * ctx.delta_time;
            }
            if (ctx.input_state.key_s) {
                m_position.y -= speed * ctx.delta_time;
            }
            break;
        }
        case PaddleType::Right: {
            if (ctx.input_state.key_up) {
                m_position.y += speed * ctx.delta_time;
            }
            if (ctx.input_state.key_down) {
                m_position.y -= speed * ctx.delta_time;
            }
            break;
        }
        case PaddleType::Single: {
            if (ctx.input_state.key_left) {
                m_position.x -= speed * ctx.delta_time;
            }
            if (ctx.input_state.key_right) {
                m_position.x += speed * ctx.delta_time;
            }
            break;
        }
        }

        m_position.y = std::clamp(m_position.y, -1.0f, 1.0f - m_size.y);
        m_position.x = std::clamp(m_position.x, -1.0f, 1.0f - m_size.x);
    }

} // namespace pong
