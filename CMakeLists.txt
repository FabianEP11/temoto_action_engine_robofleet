cmake_minimum_required(VERSION 3.0.2)
project(temoto_action_engine_robofleet)

find_package(catkin REQUIRED COMPONENTS
  robofleet_client
  temoto_action_engine
  
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES temoto_action_engine_robofleet
  CATKIN_DEPENDS
    robofleet_client
    temoto_action_engine
    
)

set(PLUGIN_SRC
	src/StartUmrfGraph.cpp
	src/BroadcastStopUmrfGraph.cpp
	src/UmrfGraphDiff.cpp
	src/BroadcastStartUmrfGraph.cpp
	src/GetUmrfGraphs.cpp
	src/StopUmrfGraph.cpp
)

add_library(temoto_action_engine_robofleet ${PLUGIN_SRC})
target_link_libraries(temoto_action_engine_robofleet ${catkin_LIBRARIES})
target_include_directories(temoto_action_engine_robofleet PRIVATE
  include
  ${catkin_INCLUDE_DIRS}
)
