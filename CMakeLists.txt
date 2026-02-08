cmake_minimum_required(VERSION 4.2.1)

project(flappy_bird)

add_subdirectory(deps)

set(FLAPPY_BIRD_SOURCES
    "src/main.cpp"
    "src/game.cpp"
    "src/asset_manager.cpp"
    "src/state_manager.cpp"
    "src/player.cpp"
    "src/pipe_spawner.cpp"
)

add_executable(flappy_bird ${FLAPPY_BIRD_SOURCES})
target_link_libraries(flappy_bird PRIVATE raylib_static)