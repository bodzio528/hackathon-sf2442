cmake_minimum_required(VERSION 3.6)

project(sf2442 LANGUAGES CXX)

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

set(LOGIC_SRC
    src/Game.cpp
    src/Logic.cpp
    src/CourseCalculator.cpp
)

set(MAIN_SRC
    src/main.cpp
)

add_custom_target(Cumulative ALL)
add_custom_command(TARGET Cumulative PRE_BUILD
    COMMAND # find all #include <> and save then to Includes.cpp
        grep -h -e "'^#include <[^>]*>'" -r include/ src/ |
        sort -u | cat - > ${CMAKE_CURRENT_BINARY_DIR}/Includes.cpp
    COMMAND
        cat ${LOGIC_SRC} ${MAIN_SRC} |
        ${CMAKE_CXX_COMPILER} -x c++ -E -P -DSF2442_CUMULATIVE -nostdinc++ -std=c++11 -I./include - |
        cat -s ${CMAKE_CURRENT_BINARY_DIR}/Includes.cpp - > ${CMAKE_CURRENT_BINARY_DIR}/Cumulative.cpp
#    COMMAND # remove intermediate
#        rm ${CMAKE_CURRENT_BINARY_DIR}/Includes.cpp
    DEPENDS ${HDR_LIST} ${LOGIC_SRC} ${MAIN_SRC}
    COMMENT "Generate cumulative C++ source from preprocessor output"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(Logic ${LOGIC_SRC})

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${HDR_LIST})
target_link_libraries(${PROJECT_NAME} Logic)

add_subdirectory(googletest-master)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

set(MOCK_LIST
    test/mock/GameMock.hpp
    test/mock/CourseCalculatorMock.hpp
)

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

add_executable(UTexe ${TEST_SUITES} ${MOCK_LIST})
target_link_libraries(UTexe Logic gmock gmock_main)
add_test(run_UTexe UTexe)
