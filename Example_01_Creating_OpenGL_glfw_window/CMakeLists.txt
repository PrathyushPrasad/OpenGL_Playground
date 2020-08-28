set(PROJECT_NAME "Example_01")

project(${PROJECT_NAME})

set(PROJECT_CXX_HEADERS
    "cxxheaders"
    )
    
set(PROJECT_CXX_SOURCES
    "cxxsources"
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -g -O0")

pkg_check_modules(REQUIRED_COMPONENTS REQUIRED
    glfw3
    glew
)

include_directories(
    ${REQUIRED_COMPONENTS_INCLUDE_DIRS}
    ${PROJECT_CXX_HEADERS}
    )
    
link_directories(
    ${REQUIRED_COMPONENTS_LIBRARY_DIRS}
    ${CMAKE_HOME_DIRECTORY}/_output/lib
    )

file(GLOB SOURCES
    "${PROJECT_CXX_SOURCES}/*.c"
    "${PROJECT_CXX_SOURCES}/*.cc"
    "${PROJECT_CXX_SOURCES}/*.cpp"
    )
    
add_executable(${PROJECT_NAME}
    ${SOURCES}
    )

target_link_libraries(${PROJECT_NAME}
    ${REQUIRED_COMPONENTS_LIBRARIES}
    )

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build_output/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build_output/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build_output/bin"
    )
