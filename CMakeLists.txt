cmake_minimum_required(VERSION 3.20)
project(AVL_Tree LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

option(COPY_RESOURCES "Enable copying resource files to the build directory" ON)
option(ENABLE_VENDOR_LIBS "Enable building vendor libraries" ON)

# find_package(<insert> REQUIRED)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/<insert>)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
add_executable(Tests 
    ${TEST_SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AVLTree.cpp
    ${HEADERS}
)
# target_link_libraries(
#   ${INSERT_PROJECT_NAME} 
#   PRIVATE 
#       PACKAGE_0 
#       PACKAGE_1
# )

target_include_directories(
    ${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_include_directories(
    Tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
)

# Copy resource files to build dir
if (COPY_RESOURCES)
    file(GLOB RSC_FILES "${CMAKE_SOURCE_DIR}/rsc/*")
    foreach(file ${RSC_FILES})
        file(COPY ${file} DESTINATION ${CMAKE_BINARY_DIR}/rsc/)
    endforeach()
endif()


# Copy commands for clangd
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()