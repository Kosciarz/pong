set(SOURCES
    "Main.cpp"
    "Engine.cpp"
    "OpenGLDebugCallback.cpp"
)

set(HEADERS
    "OpenGLHeaders.hpp"
    "Engine.hpp"
    "OpenGLDebugCallback.hpp"
)

add_executable(pong ${SOURCES} ${HEADERS})
target_link_libraries(pong
    PRIVATE OpenGL::GL glfw glad glm
)
