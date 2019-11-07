set(BLYSS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BLYSS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

function(ADD_SRC_ROOT FILE_NAME)
    list(APPEND BLYSS_SRCS "${BLYSS_SOURCE_DIR}/${FILE_NAME}.cpp")
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_SOURCE_DIR}/${FILE_NAME}.cpp
    )
endfunction(ADD_SRC_ROOT)

function(ADD_SRC FILE_NAME FOLDER)
    list(APPEND BLYSS_SRCS "${BLYSS_SOURCE_DIR}/${FOLDER}/${FILE_NAME}.cpp")
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_SOURCE_DIR}/${FOLDER}/${FILE_NAME}.cpp
    )
endfunction(ADD_SRC)

function(ADD_HDR_ROOT FILE_NAME)
    list(APPEND BLYSS_HDRS "${BLYSS_INCLUDE_DIR}/${FILE_NAME}.hpp")
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_INCLUDE_DIR}/${FILE_NAME}.hpp
    )
endfunction(ADD_HDR_ROOT)

function(ADD_HDR FILE_NAME FOLDER)
    list(APPEND BLYSS_HDRS "${BLYSS_INCLUDE_DIR}/${FOLDER}/${FILE_NAME}.hpp")
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)

    source_group(${FOLDER} FILES
        ${BLYSS_INCLUDE_DIR}/${FOLDER}/${FILE_NAME}.hpp
    )
endfunction(ADD_HDR)

function(ADD_CLASS_ROOT FILE_NAME)
    ADD_SRC_ROOT(${FILE_NAME})
    ADD_HDR_ROOT(${FILE_NAME})
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)
endfunction(ADD_CLASS_ROOT)

function(ADD_CLASS FILE_NAME FOLDER)
    ADD_SRC(${FILE_NAME} ${FOLDER})
    ADD_HDR(${FILE_NAME} ${FOLDER})
    set(BLYSS_SRCS ${BLYSS_SRCS} PARENT_SCOPE)
    set(BLYSS_HDRS ${BLYSS_HDRS} PARENT_SCOPE)
endfunction(ADD_CLASS)