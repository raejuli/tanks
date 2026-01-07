cmake_minimum_required(VERSION 4.0)
project(engine)

set(CMAKE_CXX_STANDARD 20)

add_library(engine STATIC
        assets/AssetManager.cpp
        entity/Entity.cpp
        component/Component.cpp
        transform/TransformComponent.cpp
        window/Window.cpp
        tree/Tree.cpp
        scene/SceneTree.cpp
        renderer/shader/Shader.cpp
        renderer/shader/VertexShader.cpp
        renderer/shader/FragmentShader.cpp
        renderer/components/RendererComponent.cpp
        renderer/components/QuadRenderer.cpp
        renderer/components/Texture2DComponent.cpp
        renderer/texture/Texture2D.cpp
        renderer/Camera.cpp
        renderer/SceneRenderer.cpp
)

target_include_directories(engine PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/external/stb
)

# Link to glad (defined in parent CMakeLists.txt)
target_link_libraries(engine PUBLIC
        glad
        glfw3
        opengl32    # Windows OpenGL library
        )