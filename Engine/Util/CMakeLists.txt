
SET(_TARGET DuskUtil)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        $<$<CXX_COMPILER_ID:Clang>:stdc++fs>
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>
)
