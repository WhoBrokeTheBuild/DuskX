
SET(_TARGET PreCommit)

ADD_EXECUTABLE(${_TARGET} "")

FILE(GLOB_RECURSE
    _PRIVATE
    Private/*.cpp
    Private/*.c
    Private/*.hpp
    Private/*.h
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

FILE(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/pre-commit.$<CONFIG>"
    INPUT "${CMAKE_CURRENT_SOURCE_DIR}/pre-commit.in"
)

ADD_CUSTOM_COMMAND(
    TARGET ${_TARGET} POST_BUILD
    BYPRODUCTS "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_BINARY_DIR}/pre-commit.$<CONFIG>"
        "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit"
)
