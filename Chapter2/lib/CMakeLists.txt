add_library(graphics_lib STATIC canvas.cpp raytracing.cpp)
target_include_directories(graphics_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(graphics_lib raylib)

set_target_properties(graphics_lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)