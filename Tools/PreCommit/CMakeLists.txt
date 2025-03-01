
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
        Threads::Threads
)

FILE(GENERATE
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/pre-commit.$<CONFIG>"
    INPUT "${CMAKE_CURRENT_SOURCE_DIR}/pre-commit.in"
)

IF(NOT WIN32)
    SET(SET_EXECUTABLE_COMMAND chmod +x "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit")
ENDIF()

ADD_CUSTOM_COMMAND(
    TARGET ${_TARGET} POST_BUILD
    BYPRODUCTS "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_BINARY_DIR}/pre-commit.$<CONFIG>"
        "${CMAKE_SOURCE_DIR}/.git/hooks/pre-commit"
    COMMAND ${SET_EXECUTABLE_COMMAND}
)
