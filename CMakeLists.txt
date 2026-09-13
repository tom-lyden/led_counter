cmake_minimum_required(VERSION 4.3)
project(led_counter C)

set(CMAKE_C_STANDARD 23)

add_executable(led_counter src/main.c
        include/board_definition.h)

target_sources(led_counter
        PRIVATE
        platform/stm32f4xx_startup.c
        utils/src/timer.c
)

set_source_files_properties(platform/stm32f4xx_startup.c
    PROPERTIES COMPILE_OPTIONS "-fno-tree-loop-distribute-patterns;-save-temps=obj"
)

include(FetchContent)

FetchContent_Declare(
        f401_re_hal
        GIT_REPOSITORY https://github.com/tom-lyden/f401_re_hal.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(f401_re_hal)

target_link_libraries(led_counter
        f401_re_hal
)

target_include_directories(led_counter 
        PRIVATE
        include
        utils/include
)
