set(SOURCES
    "Main.cpp"
)

set(HEADERS

)

add_executable(pong ${SOURCES} ${HEADERS})
target_link_libraries(pong
    PRIVATE OpenGL::GL glfw glad glm
)
