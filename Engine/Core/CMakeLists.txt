
SET(_TARGET DuskCore)

DuskModule(${_TARGET})

TARGET_LINK_LIBRARIES(
    ${_TARGET}
    PUBLIC
        glm
)
