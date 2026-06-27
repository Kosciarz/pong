#include "Collision.hpp"

#include "Ball.hpp"
#include "Paddle.hpp"

namespace pong {

    [[nodiscard]] bool Collision::ball_left_paddle(const Ball& ball,
                                                   const Paddle& paddle,
                                                   const float aspect_ratio) {
        const float paddle_right = (paddle.position().x + paddle.size().x) * aspect_ratio;
        const float paddle_bottom = paddle.position().y;
        const float paddle_top = paddle.position().y + paddle.size().y;

        const float ball_left = ball.position().x - ball.radius();
        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_top = ball.position().y + ball.radius();

        return ball_left <= paddle_right && ball_bottom <= paddle_top && ball_top >= paddle_bottom;
    }

    [[nodiscard]] bool Collision::ball_right_paddle(const Ball& ball,
                                                    const Paddle& paddle,
                                                    const float aspect_ratio) {
        const float paddle_left = paddle.position().x * aspect_ratio;
        const float paddle_bottom = paddle.position().y;
        const float paddle_top = paddle.position().y + paddle.size().y;

        const float ball_right = ball.position().x + ball.radius();
        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_top = ball.position().y + ball.radius();

        return ball_right >= paddle_left && ball_bottom <= paddle_top && ball_top >= paddle_bottom;
    }

    [[nodiscard]] bool Collision::ball_single_paddle(const Ball& ball,
                                                     const Paddle& paddle,
                                                     const float aspect_ratio) {
        const float paddle_top = paddle.position().y + paddle.size().y;
        const float paddle_left = paddle.position().x * aspect_ratio;
        const float paddle_right = (paddle.position().x + paddle.size().x) * aspect_ratio;

        const float ball_bottom = ball.position().y - ball.radius();
        const float ball_left = ball.position().x - ball.radius();
        const float ball_right = ball.position().x + ball.radius();

        return ball_bottom <= paddle_top && ball_right >= paddle_left && ball_left <= paddle_right;
    }
} // namespace pong
