include(FetchContent)

if(COMPLEX_INCLUDE_TESTS)
  # ------------- GoogleTest --------------

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.13.0
  )
  set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
  set(BUILD_GTEST ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)
endif()