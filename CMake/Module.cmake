MACRO(DuskModule target)

ADD_LIBRARY(${target} "")

FILE(GLOB_RECURSE
    _PUBLIC
    Public/*.cpp
    Public/*.c
    Public/*.hpp
    Public/*.h
)

FILE(GLOB_RECURSE
    _PRIVATE
    Private/*.cpp
    Private/*.c
    Private/*.hpp
    Private/*.h
)

TARGET_INCLUDE_DIRECTORIES(
    ${target}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Private"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Public"
)

TARGET_SOURCES(
    ${target}
    PRIVATE ${_PRIVATE} ${_PUBLIC}
)

TARGET_COMPILE_FEATURES(
    ${target}
    PRIVATE
        cxx_std_17
)

TARGET_COMPILE_OPTIONS(
    ${target}
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/MT>
)

TARGET_LINK_OPTIONS(
    ${target}
    PUBLIC
        $<$<CXX_COMPILER_ID:MSVC>:/NODEFAULTLIB:MSVCRT /NODEFAULTLIB:LIBCMT>
)

FILE(RELATIVE_PATH folder ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
SET_TARGET_PROPERTIES(
    ${target}
    PROPERTIES FOLDER "${folder}"
)

IF(BUILD_TESTS)
    FILE(GLOB_RECURSE
        _TESTS
        "${CMAKE_CURRENT_SOURCE_DIR}/Test/*Test.cpp"
    )

    FOREACH(_test ${_TESTS})
        GET_FILENAME_COMPONENT(_name ${_test} NAME_WE)

        ADD_EXECUTABLE(
            ${_name}
            ${_test}
        )

        TARGET_LINK_LIBRARIES(
            ${_name}
            PRIVATE
                ${target}
                GTest::gtest
                GTest::gtest_main
                $<$<CXX_COMPILER_ID:MSVC>:msvcrt>
        )

        FILE(RELATIVE_PATH folder ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
        SET_TARGET_PROPERTIES(
            ${_name}
            PROPERTIES FOLDER "${folder}/Tests"
        )

        ADD_TEST(
            NAME ${_name}
            COMMAND ${_name}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    ENDFOREACH()
ENDIF()

ENDMACRO()
