#include "Game.hpp"

#include <glm/glm.hpp>
#include <print>

namespace {

    [[nodiscard]] bool check_left_paddle_collision(const pong::Ball& ball,
                                                   const pong::Paddle& paddle,
                                                   const float aspect_ratio) {
        const float paddle_right_edge = (paddle.position().x + paddle.size().x) * aspect_ratio;
        return ball.position().x - ball.radius() <= paddle_right_edge &&
               ball.position().y + ball.radius() >= paddle.position().y &&
               ball.position().y - ball.radius() <= paddle.position().y + paddle.size().y;
    }

    [[nodiscard]] bool check_right_paddle_collision(const pong::Ball& ball,
                                                    const pong::Paddle& paddle,
                                                    const float aspect_ratio) {
        const float paddle_left_edge = paddle.position().x * aspect_ratio;
        return ball.position().x + ball.radius() >= paddle_left_edge &&
               ball.position().y + ball.radius() >= paddle.position().y &&
               ball.position().y - ball.radius() <= paddle.position().y + paddle.size().y;
    }

    void handle_left_paddle_collision(pong::Ball& ball, const pong::Paddle& paddle) {
        ball.set_velocity(ball.velocity() * glm::vec2{-1.0f, 1.0f});
    }

    void handle_right_paddle_collision(pong::Ball& ball, const pong::Paddle& paddle) {
        ball.set_velocity(ball.velocity() * glm::vec2{-1.0f, 1.0f});
    }

} // namespace

namespace pong {

    Game::Game()
        : m_left_paddle{glm::vec2{-0.95f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Left},
          m_right_paddle{glm::vec2{0.9f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Right},
          m_ball{glm::vec2{0.0f, 0.0f}, 0.03f} {}

    void Game::update(const GameContext& ctx) {
        m_left_paddle.update(ctx);
        m_right_paddle.update(ctx);
        m_ball.update(ctx);

        if (check_left_paddle_collision(m_ball, m_left_paddle, ctx.aspect_ratio)) {
            std::println("Left paddle collision");
            handle_left_paddle_collision(m_ball, m_left_paddle);
        }
        if (check_right_paddle_collision(m_ball, m_right_paddle, ctx.aspect_ratio)) {
            std::println("Right paddle collision");
            handle_right_paddle_collision(m_ball, m_right_paddle);
        }
    }

    void Game::render() {
        m_left_paddle.render();
        m_right_paddle.render();
        m_ball.render();
    }

} // namespace pong
