#pragma once

#include "Paddle.hpp"
#include "Ball.hpp"
#include "InputHandler.hpp"
#include "Renderer.hpp"

namespace pong {

    enum class GameState { TwoPlayer, SinglePlayer };

    struct GameContext {
        float delta_time;
        float aspect_ratio;
        InputState input_state;
    };

    class Game {
    public:
        Game();

        void update(const GameContext& ctx);
        void render(Renderer& renderer);

    private:
        GameState m_state = GameState::TwoPlayer;

        Paddle m_left_paddle;
        Paddle m_right_paddle;
        Ball m_ball;

        Paddle m_single_paddle;
        Ball m_single_ball;
    };

} // namespace pong

