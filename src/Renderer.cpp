#include "Renderer.hpp"
#include "Shader.hpp"
#include "OpenGLHeaders.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <array>
#include <vector>
#include <numbers>

namespace pong {

    Renderer::Renderer(const int width, const int height)
        : m_shader{SHADER_DIRECTORY / "vertex.vert", SHADER_DIRECTORY / "fragment.frag"} {
        {
            std::array<glm::vec2, 4> vertices = {{
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f},
            }};

            std::array<unsigned int, 6> indices{0, 1, 2, 2, 3, 0};

            glCreateVertexArrays(1, &m_quad_vao);
            glCreateBuffers(1, &m_quad_vbo);
            glCreateBuffers(1, &m_quad_ebo);

            glNamedBufferData(
                m_quad_vbo, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);
            glNamedBufferData(
                m_quad_ebo, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

            glVertexArrayVertexBuffer(m_quad_vao, 0, m_quad_vbo, 0, sizeof(glm::vec2));
            glVertexArrayElementBuffer(m_quad_vao, m_quad_ebo);

            glEnableVertexArrayAttrib(m_quad_vao, 0);
            glVertexArrayAttribFormat(m_quad_vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(m_quad_vao, 0, 0);
        }

        {
            constexpr auto segments = 100;

            std::vector<float> vertices;
            vertices.reserve((segments + 2) * 2);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);

            const float m_radius = 0.03f;

            for (int i = 0; i < segments; ++i) {
                const float theta = 2.0f * std::numbers::pi_v<float> * i / segments;

                vertices.push_back(m_radius * std::cos(theta));
                vertices.push_back(m_radius * std::sin(theta));
            }

            vertices.push_back(0.0f + m_radius);
            vertices.push_back(0.0f);

            glCreateVertexArrays(1, &m_circle_vao);
            glCreateBuffers(1, &m_circle_vbo);

            glNamedBufferData(
                m_circle_vbo, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glVertexArrayVertexBuffer(m_circle_vao, 0, m_circle_vbo, 0, sizeof(glm::vec2));

            glEnableVertexArrayAttrib(m_circle_vao, 0);
            glVertexArrayAttribFormat(m_circle_vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(m_circle_vao, 0, 0);

            m_circle_vertex_count = vertices.size() / 2;
        }

        const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
        m_projection = glm::ortho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f);
    }

    Renderer::~Renderer() {}

    void Renderer::on_resize(const int width, const int height) {
        glViewport(0, 0, width, height);

        const float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
        m_projection = glm::ortho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f);
    }

    void Renderer::clear_screen() const {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw_quad(const glm::vec2& pos, const glm::vec2& size) {
        glm::mat4 model = glm::mat4{1.0f};
        model = glm::translate(model, glm::vec3{pos, 0.0f});
        model = glm::scale(model, glm::vec3{size, 1.0f});

        const glm::mat4 projection{1.0f};

        m_shader.use();
        glUniformMatrix4fv(m_shader.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(
            m_shader.uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(m_quad_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::draw_circle(const glm::vec2& pos, const float radius) {
        const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3{pos, 0.0f});

        m_shader.use();
        glUniformMatrix4fv(m_shader.uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(
            m_shader.uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

        glBindVertexArray(m_circle_vao);
        glDrawArrays(GL_TRIANGLE_FAN, 0, m_circle_vertex_count);
    }

} // namespace pong
