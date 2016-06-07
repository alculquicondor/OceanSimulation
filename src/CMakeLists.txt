set(HEADER_FILES ${CMAKE_SOURCE_DIR}/include)
include_directories(${HEADER_FILES})

set(SOURCE_FILES main.cpp
        ${HEADER_FILES}/scene.h scene.cpp
        ${HEADER_FILES}/drawable.h drawable.cpp
        ${HEADER_FILES}/camera.h
        ${HEADER_FILES}/ortho_camera.h ortho_camera.cpp
        ${HEADER_FILES}/buffer.h buffer.cpp
        ${HEADER_FILES}/gizmo.h gizmo.cpp
        ${HEADER_FILES}/program.h program.cpp
        ${HEADER_FILES}/mvp_program.h mvp_program.cpp
        ${HEADER_FILES}/regular_polygon.h regular_polygon.cpp
        ${HEADER_FILES}/uniform_color.h uniform_color.cpp
        ${HEADER_FILES}/perspective_camera.h perspective_camera.cpp
        ${HEADER_FILES}/ocean.h ocean.cpp
        ${HEADER_FILES}/ocean_program.h ocean_program.cpp
        ${HEADER_FILES}/texture.h texture.cpp)

add_executable(ocean ${SOURCE_FILES})
target_link_libraries(ocean ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${FreeImage_LIBRARIES})

add_subdirectory(shaders)

file(COPY ocean.tga normal.tga DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
