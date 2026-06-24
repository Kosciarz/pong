#include "Game.hpp"

#include <glm/glm.hpp>

namespace pong {

    Game::Game()
        : m_paddle_left{glm::vec2{-0.95f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Left},
          m_paddle_right{glm::vec2{0.9f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Right},
          m_ball{glm::vec2{0.0f, 0.0f}, 0.03f} {}

    void Game::update(const GameContext& ctx) {
        m_paddle_left.update(ctx);
        m_paddle_right.update(ctx);
        m_ball.update(ctx);
    }

    void Game::render() {
        m_paddle_left.render();
        m_paddle_right.render();
        m_ball.render();
    }

} // namespace pong
