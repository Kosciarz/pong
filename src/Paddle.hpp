#pragma once

#include <glm/glm.hpp>

namespace pong {

    struct GameContext;

    enum class PaddleType { Left, Right, Single };

    class Paddle {
    public:
        Paddle(const glm::vec2& position, const glm::vec2& size, const PaddleType type);

        void update(const GameContext& ctx);

        [[nodiscard]] const glm::vec2& position() const { return m_position; }
        [[nodiscard]] const glm::vec2& size() const { return m_size; }
        [[nodiscard]] PaddleType type() const { return m_type; }

        void set_position(const glm::vec2& pos) { m_position = pos; }
        void set_size(const glm::vec2& size) { m_size = size; }

    private:
        glm::vec2 m_position;
        glm::vec2 m_size;
        PaddleType m_type;
    };

} // namespace pong
