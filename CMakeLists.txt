cmake_minimum_required(VERSION 3.19)
project(SpaceInvadersSFMLClone VERSION 1.0)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2
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
    include/ScoreLifeManager.h
    include/ShootingEnemy.h
    include/SpecialObject.h
    include/EnemyBullet.h
    include/GameOverWindow.h
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
    source/ScoreLifeManager.cpp
    source/ShootingEnemy.cpp
    source/SpecialObject.cpp
    source/EnemyBullet.cpp
    source/GameOverWindow.cpp
)

set(PROJECT_FILES 
    ${PROJECT_HEADERS} 
    ${PROJECT_SOURCES}
)

FetchContent_MakeAvailable(SFML)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(
    SpaceInvadersSFMLClone
    ${PROJECT_FILES}
)

# Add include directories
target_include_directories(
    SpaceInvadersSFMLClone
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    SpaceInvadersSFMLClone
    sfml-graphics
    nlohmann_json::nlohmann_json
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

