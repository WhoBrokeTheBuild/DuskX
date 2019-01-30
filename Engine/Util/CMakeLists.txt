
SET(_TARGET DuskUtil)

ADD_LIBRARY(${_TARGET} SHARED "")

FILE(GLOB_RECURSE 
    _PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h"
)

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
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Public"
)

TARGET_SOURCES(
    ${_TARGET}
    PRIVATE ${_PRIVATE}
    PUBLIC ${_PUBLIC}
)

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)

TARGET_COMPILE_FEATURES(
    ${_TARGET} 
    PRIVATE
        cxx_std_17
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
                ${_TARGET}
                GTest::gtest
                GTest::gtest_main
        )
        ADD_TEST(
            NAME ${_name}
            COMMAND ${_name}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    ENDFOREACH()
ENDIF()