cmake_minimum_required(VERSION 3.14)
project(lab_6)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library from your implementation
add_library(DungeonEditorLib STATIC
    src/dungeon_editor.cpp
    src/npc/npc.cpp
    src/npc/orc.cpp
    src/npc/squirrel.cpp
    src/npc/druid.cpp
    src/factory/npc_factory.cpp
    src/visitor/battle_visitor.cpp
    src/observer/console_observer.cpp
    src/observer/file_observer.cpp
)

# Include directories
target_include_directories(DungeonEditorLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set properties for the library
target_compile_features(DungeonEditorLib PUBLIC cxx_std_17)

# Main executable
add_executable(main
    src/main.cpp
)
target_link_libraries(main
    DungeonEditorLib
)

# Download GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(tests 
    tests/test_npc.cpp
    tests/test_dungeon.cpp
)

# Link test executable with library and gtest
target_link_libraries(tests 
    DungeonEditorLib 
    GTest::gtest_main
)

# Include directories for tests
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Register tests
include(GoogleTest)
gtest_discover_tests(tests
    TEST_PREFIX "lab6_"
    TEST_SUFFIX ""
)

# Optional: Add post-build events or custom targets
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
    COMMENT "Running tests..."
)

add_custom_target(run_main
    COMMAND main
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running main program..."
)

# Set output directories for better organization (optional)
set_target_properties(main tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(DungeonEditorLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)