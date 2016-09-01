cmake_minimum_required(VERSION 3.1)

project(sf2442)

set(CMAKE_CXX_STANDARD 11)

include_directories(./include)

set(HDR_LIST
    include/Geometry.hpp
    include/Command.hpp
    include/IGame.hpp
    include/Game.hpp
    include/CourseCalculator.hpp
    include/ICourseCalculator.hpp
    include/Drone.hpp
    include/Logic.hpp
)

set(MOCK_LIST
    test/mock/GameMock.hpp
    test/mock/CourseCalculatorMock.hpp
)

add_custom_target(syntax
    COMMAND clang ${CMAKE_CXX_FLAGS} -std=c++11 -fsyntax-only ${HDR_LIST} ${MOCK_LIST}
    SOURCES ${HDR_LIST} ${MOCK_LIST})

add_custom_target(cumulative
    COMMAND clang++ -E -P ${CMAKE_CXX_FLAGS} -DAAA -nostdinc++ -std=c++11 -I${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src/Cumulative.cpp > ${CMAKE_CURRENT_BINARY_DIR}/cumulative.cpp
    SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Cumulative.cpp)

set(LOGIC_SRC
    src/Game.cpp
    src/Logic.cpp
    src/CourseCalculator.cpp
)

add_library(Logic ${LOGIC_SRC})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Logic)

add_subdirectory(googletest-master)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(TEST_SUITES
    test/CommandTestSuite.cpp
    test/GameTestSuite.cpp
    test/LogicTestSuite.cpp
    test/CourseCalculatorTestSuite.cpp
)

foreach (test_suite_file ${TEST_SUITES})
    get_filename_component(test_suite_name ${test_suite_file} NAME_WE)
    add_executable(${test_suite_name} ${test_suite_file})
    target_link_libraries(${test_suite_name} Logic gmock gmock_main)
    add_test(run_${test_suite_name} ${test_suite_name})
endforeach()

add_executable(UTexe ${TEST_SUITES})
target_link_libraries(UTexe Logic gmock gmock_main)
add_test(run_UTexe UTexe)
