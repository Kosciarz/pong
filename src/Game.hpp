#pragma once

#include "Paddle.hpp"
#include "Ball.hpp"
#include "InputHandler.hpp"

namespace pong {

    struct GameContext {
        float delta_time;
        float aspect_ratio;
        InputState input_state;
    };

    class Game {
    public:
        Game();

        void update(const GameContext& ctx);
        void render();

    private:
        Paddle m_paddle1;
        Paddle m_paddle2;
        Ball m_ball;
    };

} // namespace pong

