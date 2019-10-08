cmake_minimum_required(VERSION 3.12)
project(rocket_src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)


set(SOURCE_FILES
        BaseObject.h
        Collision.cpp
        Collision.h
        GameContainer.cpp
        GameContainer.h
        GameObjects.cpp
        GameObjects.h
        main.cpp
        Meteor.cpp
        Meteor.h
        Rocket.cpp
        Rocket.h)

add_executable(rocket_src ${SOURCE_FILES})
target_link_libraries(rocket_src sfml-system sfml-window sfml-graphics sfml-audio sfml-network png)