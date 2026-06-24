#pragma once

#include "OpenGLHeaders.hpp"

#include <filesystem>

namespace pong {

    inline static const std::filesystem::path SHADER_DIRECTORY{SHADER_DIR};

    class Shader {
    public:
        Shader(const std::filesystem::path& vertex_path,
               const std::filesystem::path& fragment_path);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&&) noexcept;
        Shader& operator=(Shader&&) noexcept;

        void use() const { glUseProgram(m_program); }
        void unuse() const { glUseProgram(0); }

        [[nodiscard]] GLint uniform_location(const char* name) const;

    private:
        GLuint m_program;
    };

} // namespace pong

