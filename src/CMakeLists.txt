set(SOURCES
    "Main.cpp"
    "Engine.cpp"
    "OpenGLDebugCallback.cpp"
    "Shader.cpp"
    "Game.cpp"
    "Paddle.cpp"
    "Ball.cpp"
    "InputHandler.cpp"
    "Collision.cpp"
    "Renderer.cpp"
)

set(HEADERS
    "OpenGLHeaders.hpp"
    "Engine.hpp"
    "OpenGLDebugCallback.hpp"
    "Shader.hpp"
    "Game.hpp"
    "Paddle.hpp"
    "Ball.hpp"
    "InputHandler.hpp"
    "Collision.hpp"
    "Renderer.hpp"
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
