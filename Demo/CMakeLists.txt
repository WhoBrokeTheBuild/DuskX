
SET(_TARGET "Demo")

ADD_EXECUTABLE(${_TARGET} "")

FILE(GLOB_RECURSE 
    _PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.h"
)

TARGET_INCLUDE_DIRECTORIES(
    ${_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Private"
)

TARGET_SOURCES(
    ${_TARGET}
    PRIVATE ${_PRIVATE}
)

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PRIVATE
        DuskCore
        DuskDesktop
        DuskUtil
)

TARGET_COMPILE_FEATURES(
    ${_TARGET} 
    PRIVATE
        cxx_std_17
)