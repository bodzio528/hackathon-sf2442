cmake_minimum_required(VERSION 3.6)

project(sf2442 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(./include)

set(HDR_LIST
    include/Geometry.hpp
    include/Command.hpp
    include/IGame.hpp
    include/Game.hpp
    include/CourseCalculator.hpp
    include/ICourseCalculator.hpp
    include/TargetCalculator.hpp
    include/ITargetCalculator.hpp
    include/Drone.hpp
    include/Logic.hpp
    include/IBoostCalculator.hpp
    include/BoostCalculator.hpp
    include/ILapCalculator.hpp
    include/LapCalculator.hpp
)

set(LOGIC_SRC
    src/Game.cpp
    src/Logic.cpp
    src/CourseCalculator.cpp
    src/TargetCalculator.cpp
    src/BoostCalculator.cpp
    src/LapCalculator.cpp
)

set(MAIN_SRC
    src/main.cpp
)

add_custom_target(Cumulative ALL DEPENDS Cumulative.cpp)
add_custom_command(OUTPUT Cumulative.cpp
    COMMAND
        cat ${LOGIC_SRC} ${MAIN_SRC} |
        ${CMAKE_CXX_COMPILER} -x c++ -E -P -DSF2442_CUMULATIVE -nostdinc++ -std=c++11 -I./include - |
        cat -s ${CMAKE_CURRENT_BINARY_DIR}/Includes.cpp - > ${CMAKE_CURRENT_BINARY_DIR}/Cumulative.cpp
    DEPENDS Includes.cpp
    COMMENT "Generate cumulative C++ source from preprocessor output"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(OUTPUT Includes.cpp
    COMMAND
        grep -h -e "'^#include <[^>]*>'" -r include/ src/ |
        sort -u | cat - > ${CMAKE_CURRENT_BINARY_DIR}/Includes.cpp
    DEPENDS ${HDR_LIST} ${LOGIC_SRC} ${MAIN_SRC}
    COMMENT "Find all #include <> and save them to Includes.cpp"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Logic ${LOGIC_SRC})

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${HDR_LIST})
target_link_libraries(${PROJECT_NAME} Logic)

enable_testing()

add_subdirectory(googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(MOCK_LIST
    test/mock/GeometryMatchers.hpp
    test/mock/GameMock.hpp
    test/mock/CourseCalculatorMock.hpp
    test/mock/TargetCalculatorMock.hpp
    test/mock/BoostCalculatorMock.hpp
    test/mock/LapCalculatorMock.hpp
)

set(TEST_SUITES
    test/CommandTestSuite.cpp
    test/GameTestSuite.cpp
    test/LogicTestSuite.cpp
    test/CourseCalculatorTestSuite.cpp
    test/TargetCalculatorTestSuite.cpp
    test/BoostCalculatorTestSuite.cpp
    test/LapCalculatorTestSuite.cpp
)

option(BUILD_DETAILED_UNIT_TESTS "Decide whether build separate executable for each test suite" OFF)

if (BUILD_DETAILED_UNIT_TESTS)
    foreach (test_suite_file ${TEST_SUITES})
        get_filename_component(test_suite_name ${test_suite_file} NAME_WE)
        add_executable(${test_suite_name} ${test_suite_file})
        target_link_libraries(${test_suite_name} Logic gmock_main)
        add_test(run_${test_suite_name} ${test_suite_name})
    endforeach()
endif()

add_executable(UTexe ${TEST_SUITES} ${MOCK_LIST})
target_link_libraries(UTexe Logic gmock_main)
add_test(run_UTexe UTexe)
