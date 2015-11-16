cmake_minimum_required(VERSION 2.8.3)
project(os32c)

find_package(catkin REQUIRED roscpp ovda_ethernetip)

find_package(Boost 1.47 REQUIRED COMPONENTS system)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
  DEPENDS boost
)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)

add_library(os32c_lib src/os32c.cpp)
target_link_libraries(os32c_lib
  ${catkin_LIBRARIES}
)

## Declare a cpp executable
add_executable(scanner src/scanner_node.cpp)
target_link_libraries(scanner
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(os32c src/os32c_node.cpp)
target_link_libraries(os32c
  os32c_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

## Mark executables and libraries for installation
install(TARGETS scanner os32c_lib os32c
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/os32c
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

if (CATKIN_ENABLE_TESTING)
  catkin_add_gtest(os32c-test
    test/measurement_report_config_test.cpp
    test/measurement_report_header_test.cpp
    test/measurement_report_test.cpp
    test/range_and_reflectance_measurement_test.cpp
    test/os32c_test.cpp
    test/test_main.cpp
  )
  target_link_libraries(os32c-test ${Boost_LIBRARIES} eip os32c_lib)
endif()

