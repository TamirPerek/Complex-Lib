set(THIS Complextests)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(${THIS} 
    ComplexTest.cpp
    ComplexTestCustom.cpp
)

target_link_libraries(${THIS}
                        gtest_main
                        Complex-Lib
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)