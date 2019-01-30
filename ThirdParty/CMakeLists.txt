CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

INCLUDE(ExternalProject)

# glm

SET(_glm_DIR "${CMAKE_BINARY_DIR}/glm")

ExternalProject_Add(
    ThirdParty_glm
    GIT_REPOSITORY      "https://github.com/g-truc/glm.git"
    GIT_TAG             "0.9.9.3"
    GIT_SHALLOW         TRUE
    SOURCE_DIR          "${_glm_DIR}"
    BINARY_DIR          "${_glm_DIR}"
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${_glm_DIR}
                        -DGLM_TEST_ENABLE=OFF
    BUILD_COMMAND       ""
    UPDATE_COMMAND      ""
    TEST_COMMAND        ""
)

# GSL

# GTest

SET(_GSL_DIR "${CMAKE_BINARY_DIR}/GSL")
SET(_GSL_SOURCE_DIR "${CMAKE_BINARY_DIR}/GSL_src")
SET(_GSL_BINARY_DIR "${CMAKE_BINARY_DIR}/GSL_bin")

ExternalProject_Add(
    ThirdParty_GSL
    GIT_REPOSITORY      "https://github.com/Microsoft/GSL.git"
    GIT_TAG             "v2.0.0"
    GIT_SHALLOW         TRUE
    SOURCE_DIR          "${_GSL_SOURCE_DIR}"
    BINARY_DIR          "${_GSL_BINARY_DIR}"
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${_GSL_DIR}
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ${CMAKE_COMMAND} --build . --target install --config Release
    UPDATE_COMMAND      ""
    TEST_COMMAND        ""
)

# SDL2

SET(_SDL2_DIR "${CMAKE_BINARY_DIR}/SDL2")
SET(_SDL2_SOURCE_DIR "${CMAKE_BINARY_DIR}/SDL2_src")
SET(_SDL2_BINARY_DIR "${CMAKE_BINARY_DIR}/SDL2_bin")

ExternalProject_Add(
    ThirdParty_SDL2
    GIT_REPOSITORY      "https://github.com/spurious/SDL-mirror.git"
    GIT_TAG             "master"
    GIT_SHALLOW         TRUE
    SOURCE_DIR          "${_SDL2_SOURCE_DIR}"
    BINARY_DIR          "${_SDL2_BINARY_DIR}"
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${_SDL2_DIR}
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ${CMAKE_COMMAND} --build . --target install --config Release
    UPDATE_COMMAND      ""
    TEST_COMMAND        ""
)

# GTest

SET(_GTest_DIR "${CMAKE_BINARY_DIR}/GTest")
SET(_GTest_SOURCE_DIR "${CMAKE_BINARY_DIR}/GTest_src")
SET(_GTest_BINARY_DIR "${CMAKE_BINARY_DIR}/GTest_bin")

ExternalProject_Add(
    ThirdParty_GTest
    GIT_REPOSITORY      "https://github.com/google/googletest"
    GIT_TAG             "v1.8.x"
    GIT_SHALLOW         TRUE
    SOURCE_DIR          "${_GTest_SOURCE_DIR}"
    BINARY_DIR          "${_GTest_BINARY_DIR}"
    CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${_GTest_DIR}
                        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ${CMAKE_COMMAND} --build . --target install --config Release
    UPDATE_COMMAND      ""
    TEST_COMMAND        ""
)
