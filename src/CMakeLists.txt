file(GLOB_RECURSE TARGET_SRC "./*.cpp" "./*.hpp" "./*.c" "./*.h")

add_library(${This} STATIC ${TARGET_SRC})
target_sources(${This} PRIVATE ${TARGET_SRC})
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
