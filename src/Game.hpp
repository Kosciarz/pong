#pragma once

#include "Paddle.hpp"
#include "Ball.hpp"

namespace pong {

    class Game {
    public:
        Game();

        void update(const float dt, const float aspect_ratio);
        void render();

    private:
        Paddle m_paddle1;
        Paddle m_paddle2;
        Ball m_ball;
    };

} // namespace pong

