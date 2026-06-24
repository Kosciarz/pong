set(SOURCES
    "Main.cpp"
    "Engine.cpp"
    "OpenGLDebugCallback.cpp"
    "Shader.cpp"
    "Game.cpp"
    "Paddle.cpp"
)

set(HEADERS
    "OpenGLHeaders.hpp"
    "Engine.hpp"
    "OpenGLDebugCallback.hpp"
    "Shader.hpp"
    "Game.hpp"
    "Paddle.hpp"
)

add_executable(pong ${SOURCES} ${HEADERS})
target_link_libraries(pong
    PRIVATE
    OpenGL::GL glfw glad glm
)
target_compile_definitions(pong
    PRIVATE
    SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
)
