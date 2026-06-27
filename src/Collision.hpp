#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"

namespace pong {

    class Collision {
    public:
        [[nodiscard]] static bool ball_left_paddle(const Ball& ball,
                                                   const Paddle& paddle,
                                                   const float aspect_ratio);
        [[nodiscard]] static bool ball_right_paddle(const Ball& ball,
                                                    const Paddle& paddle,
                                                    const float aspect_ratio);
        [[nodiscard]] static bool ball_single_paddle(const Ball& ball,
                                                     const Paddle& paddle,
                                                     const float aspect_ratio);
    };

} // namespace pong

