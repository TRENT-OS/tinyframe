cmake_minimum_required(VERSION 3.13.0)

# enable new behavior introduced in CMake 3.13, where relative paths will be
# converted into absolute paths in target_sources(INTERFACE ....)
cmake_policy(SET CMP0076 NEW)

macro (declareIfLib)
    add_library(${PROJECT_NAME} INTERFACE)
    target_include_directories(${PROJECT_NAME}
        INTERFACE
           .
    )
endMacro()

project(third_party_tinyframe_if)
    declareIfLib()

project(third_party_tinyframe)
    declareIfLib()
    target_sources(${PROJECT_NAME}
        INTERFACE
           TinyFrame.c
    )

project(third_party_tinyframe_static_cpp CXX)
    add_library(${PROJECT_NAME} EXCLUDE_FROM_ALL STATIC)
    SET_SOURCE_FILES_PROPERTIES(TinyFrame.c
        PROPERTIES
            LANGUAGE CXX
            COMPILE_FLAGS -fpermissive
    )
    target_include_directories(${PROJECT_NAME}
        INTERFACE
           .
    )
    target_sources(${PROJECT_NAME}
        PRIVATE
           TinyFrame.c
    )
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            os_core_api
    )

