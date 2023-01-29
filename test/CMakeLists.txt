set(THIS Complextests)

add_executable(${THIS} 
    ComplexTest.cpp
    ComplexTestCustom.cpp
)

target_link_libraries(${THIS}
                        gtest_main
                        Complex
)

add_test(
    NAME ${THIS}
    COMMAND ${THIS}
)