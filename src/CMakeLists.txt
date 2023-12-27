add_library(${PROJECT_NAME} INTERFACE 
)

message(STATUS "CMake install directory: " ${CMAKE_INSTALL_INCLUDEDIR})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
