#include "Game.hpp"

#include <glm/glm.hpp>

namespace pong {

    Game::Game()
        : m_paddle1{glm::vec2{-0.95, -0.5}, glm::vec2{0.05, 1.0}},
          m_paddle2{glm::vec2{0.9, -0.5}, {0.05, 1.0}},
          m_ball{glm::vec2{0.0, 0.0}, 0.05} {}

    void Game::update(const float dt, const float aspect_ratio) {
        m_paddle1.update(dt);
        m_paddle2.update(dt);
        m_ball.update(dt, aspect_ratio);
    }

    void Game::render() {
        m_paddle1.render();
        m_paddle2.render();
        m_ball.render();
    }

} // namespace pong
