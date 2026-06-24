#include "Game.hpp"

#include <glm/glm.hpp>

namespace pong {

    Game::Game()
        : m_paddle1{glm::vec2{-0.95, -0.5}, glm::vec2{0.05, 1.0}},
          m_paddle2{glm::vec2{0.9, -0.5}, {0.05, 1.0}} {}

    void Game::update(const float dt) {
        m_paddle1.update(dt);
        m_paddle2.update(dt);
    }

    void Game::render() {
        m_paddle1.render();
        m_paddle2.render();
    }

} // namespace pong
