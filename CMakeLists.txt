cmake_minimum_required(VERSION 3.19)
project(SpaceInvadersSFMLClone VERSION 1.0)
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)

set(PROJECT_HEADERS 
include/Enemy.h
include/Bullet.h
include/Player.h
include/Game.h
include/UIManager.h
include/World.h
include/Gameobject.h
include/InputManager.h
include/EnemySpawner.h
include/TextureLoader.h
include/ObjectPooler.h
include/MyText.h
include/ProgressBar.h
include/UIGameobject.h
)

set(PROJECT_SOURCES 
main.cpp
source/Enemy.cpp
source/Bullet.cpp
source/Player.cpp
source/Game.cpp
source/UIManager.cpp
source/World.cpp
source/Gameobject.cpp
source/InputManager.cpp
source/EnemySpawner.cpp
source/TextureLoader.cpp
source/ObjectPooler.cpp
source/MyText.cpp
source/ProgressBar.cpp
source/UIGameobject.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE include )

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
 SpaceInvadersSFMLClone
 main.cpp
 ${PROJECT_FILES}
)

target_link_libraries(
 SpaceInvadersSFMLClone
 sfml-graphics
)