cmake_minimum_required(VERSION 2.8.3)
project(omron_os32c_driver)

find_package(catkin REQUIRED COMPONENTS diagnostic_updater odva_ethernetip roscpp sensor_msgs)

find_package(Boost 1.47 REQUIRED COMPONENTS system)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS diagnostic_updater odva_ethernetip roscpp sensor_msgs
  LIBRARIES omron_os32c
  DEPENDS Boost
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_library(omron_os32c src/os32c.cpp)
target_link_libraries(omron_os32c
  ${catkin_LIBRARIES}
)

## Declare a cpp executable
add_executable(scanner_node src/scanner_node.cpp)
target_link_libraries(scanner_node
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(omron_os32c_node src/os32c_node.cpp)
target_link_libraries(omron_os32c_node
  omron_os32c
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

## Mark executables and libraries for installation
install(TARGETS omron_os32c omron_os32c_node scanner_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

if (CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch/os32c.launch)

  catkin_add_gtest(${PROJECT_NAME}-test
    test/measurement_report_config_test.cpp
    test/measurement_report_header_test.cpp
    test/measurement_report_test.cpp
    test/range_and_reflectance_measurement_test.cpp
    test/os32c_test.cpp
    test/test_main.cpp
  )
  target_link_libraries(${PROJECT_NAME}-test ${Boost_LIBRARIES} ${catkin_LIBRARIES} omron_os32c)
endif()

