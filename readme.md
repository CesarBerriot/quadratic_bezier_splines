```cmake
    include(FetchContent)

    FetchContent_Declare(
        quadratic_bezier_splines
        GIT_REPOSITORY https://github.com/CesarBerriot/quadratic_bezier_splines.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(quadratic_bezier_splines)

    target_link_libraries(PROJECT_NAME PRIVATE quadratic_bezier_splines)
```