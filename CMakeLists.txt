# 3.7 woulb be required to find vulkan
cmake_minimum_required(VERSION 3.7)

project(draft)

# setting cpp standard
set (CMAKE_CXX_STANDARD 17)

# setting compiles flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# adding wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable( draft 
    
    src/main.cpp
    src/main_window.h
    src/main_window.cpp
    src/draft_area.h
    src/draft_area.cpp
    src/draft_painter.h
    src/draft_painter.cpp
    src/part.h
    src/part.cpp
    src/connectors.h
    src/connectors.cpp
    src/constraints.h
    src/constraints.cpp

)


set_target_properties(draft PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(draft ${wxWidgets_LIBRARIES})
target_include_directories(draft PUBLIC src extern/glm)




