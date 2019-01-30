
SET(_TARGET PreCommit)

ADD_EXECUTABLE(${_TARGET} "")

FILE(GLOB_RECURSE 
    _PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.h"
)

TARGET_SOURCES(
    ${_TARGET}
    PRIVATE ${_PRIVATE}
)

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PRIVATE
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

ADD_CUSTOM_TARGET(
    install_${_TARGET} ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:${_TARGET}>
        ${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit 
)