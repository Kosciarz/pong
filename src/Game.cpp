#include "Game.hpp"

#include <glm/glm.hpp>
#include <print>

namespace {

    [[nodiscard]] bool check_left_paddle_collision(const pong::Ball& ball,
                                                   const pong::Paddle& paddle,
                                                   const float aspect_ratio) {
        const float paddle_right = (paddle.position().x + paddle.size().x) * aspect_ratio;
        const float paddle_bottom = paddle.position().y;
        const float paddle_top = paddle.position().y + paddle.size().y;

        const float ball_left = ball.position().x - ball.radius();
        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_top = ball.position().y + ball.radius();

        return ball_left <= paddle_right && ball_bottom <= paddle_top && ball_top >= paddle_bottom;
    }

    [[nodiscard]] bool check_right_paddle_collision(const pong::Ball& ball,
                                                    const pong::Paddle& paddle,
                                                    const float aspect_ratio) {
        const float paddle_left = paddle.position().x * aspect_ratio;
        const float paddle_bottom = paddle.position().y;
        const float paddle_top = paddle.position().y + paddle.size().y;

        const float ball_right = ball.position().x + ball.radius();
        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_top = ball.position().y + ball.radius();

        return ball_right >= paddle_left && ball_bottom <= paddle_top && ball_top >= paddle_bottom;
    }

    [[nodiscard]] bool check_single_paddle_collision(const pong::Ball& ball,
                                                     const pong::Paddle& paddle,
                                                     const float aspect_ratio) {
        const float paddle_top = paddle.position().y + paddle.size().y;
        const float paddle_left = paddle.position().x * aspect_ratio;
        const float paddle_right = (paddle.position().x + paddle.size().x) * aspect_ratio;

        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_left = ball.position().x - ball.radius();
        const float ball_right = ball.position().x + ball.radius();

        return ball_bottom <= paddle_top && ball_right >= paddle_left && ball_left <= paddle_right;
    }

    void handle_left_paddle_collision(pong::Ball& ball,
                                      const pong::Paddle& paddle,
                                      const float aspect_ratio) {
        const glm::vec2 new_position{(paddle.position().x + paddle.size().x) * aspect_ratio +
                                         ball.radius(),
                                     ball.position().y};
        ball.set_position(new_position);
        ball.set_velocity(ball.velocity() * glm::vec2{-1.0f, 1.0f});
    }

    void handle_right_paddle_collision(pong::Ball& ball,
                                       const pong::Paddle& paddle,
                                       const float aspect_ratio) {
        const glm::vec2 new_position{paddle.position().x * aspect_ratio - ball.radius(),
                                     ball.position().y};
        ball.set_position(new_position);
        ball.set_velocity(ball.velocity() * glm::vec2{-1.0f, 1.0f});
    }

    void handle_single_paddle_collision(pong::Ball& ball,
                                        const pong::Paddle& paddle,
                                        const float aspect_ratio) {
        const glm::vec2 new_position{ball.position().x,
                                     paddle.position().y + paddle.size().y + ball.radius()};
        ball.set_position(new_position);
        ball.set_velocity(ball.velocity() * glm::vec2{1.0f, -1.0f});
    }

} // namespace

namespace pong {

    Game::Game()
        : m_left_paddle{glm::vec2{-0.95f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Left},
          m_right_paddle{glm::vec2{0.9f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Right},
          m_ball{glm::vec2{0.0f, 0.0f}, 0.03f, glm::vec2{0.5, 0.5f}, BallType::TwoPlayer},
          m_single_paddle{glm::vec2{-0.5f, -0.95f}, glm::vec2{1.0f, 0.05f}, PaddleType::Single},
          m_single_ball{
              glm::vec2{0.0f, 0.0f}, 0.03f, glm::vec2{0.5f, -0.5f}, BallType::SinglePlayer} {}

    void Game::update(const GameContext& ctx) {
        if (ctx.input_state.key_1) {
            m_state = GameState::TwoPlayer;
            m_left_paddle =
                Paddle{glm::vec2{-0.95f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Left};
            m_right_paddle =
                Paddle{glm::vec2{0.9f, -0.5f}, glm::vec2{0.05f, 1.0f}, PaddleType::Right};
            m_ball = Ball{glm::vec2{0.0f, 0.0f}, 0.03f, glm::vec2{0.5, 0.5f}, BallType::TwoPlayer};
        }
        if (ctx.input_state.key_2) {
            m_state = GameState::SinglePlayer;
            m_single_paddle =
                Paddle{glm::vec2{-0.5f, -0.95f}, glm::vec2{1.0f, 0.05f}, PaddleType::Single};
            m_single_ball =
                Ball{glm::vec2{0.0f, 0.0f}, 0.03f, glm::vec2{0.5f, -0.5f}, BallType::SinglePlayer};
        }

        switch (m_state) {
        case GameState::TwoPlayer: {
            m_left_paddle.update(ctx);
            m_right_paddle.update(ctx);
            m_ball.update(ctx);

            if (check_left_paddle_collision(m_ball, m_left_paddle, ctx.aspect_ratio)) {
                handle_left_paddle_collision(m_ball, m_left_paddle, ctx.aspect_ratio);
            }
            if (check_right_paddle_collision(m_ball, m_right_paddle, ctx.aspect_ratio)) {
                handle_right_paddle_collision(m_ball, m_right_paddle, ctx.aspect_ratio);
            }
            break;
        }
        case GameState::SinglePlayer: {
            m_single_paddle.update(ctx);
            m_single_ball.update(ctx);

            if (check_single_paddle_collision(m_single_ball, m_single_paddle, ctx.aspect_ratio)) {
                handle_single_paddle_collision(m_single_ball, m_single_paddle, ctx.aspect_ratio);
            }
            break;
        }
        }
    }

    void Game::render() {
        switch (m_state) {
        case GameState::TwoPlayer: {
            m_left_paddle.render();
            m_right_paddle.render();
            m_ball.render();
            break;
        }
        case GameState::SinglePlayer: {
            m_single_paddle.render();
            m_single_ball.render();
            break;
        }
        }
    }

} // namespace pong
