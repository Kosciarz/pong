#pragma once

#include "OpenGLHeaders.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

namespace pong {

    class Renderer {
    public:
        Renderer(const int width, const int height);
        ~Renderer();

        void on_resize(const int width, const int height);

        void clear_screen() const;

        void draw_quad(const glm::vec2& pos, const glm::vec2& size);
        void draw_circle(const glm::vec2& pos, const float radius);

    private:
        GLuint m_quad_vao, m_quad_vbo, m_quad_ebo;
        GLuint m_circle_vao, m_circle_vbo;
        std::size_t m_circle_vertex_count;
        Shader m_shader;

        glm::mat4 m_projection;
    };
} // namespace pong
