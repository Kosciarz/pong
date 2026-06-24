#pragma once

#include "Paddle.hpp"

namespace pong {

    class Game {
    public:
        Game();

        void update(const float dt);
        void render();

    private:
        Paddle m_paddle1;
        Paddle m_paddle2;
    };

} // namespace pong

