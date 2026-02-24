# Console Component CMakeLists.txt

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/console.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # internal includes
    ${CMAKE_CURRENT_SOURCE_DIR}
    # external includes
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Atraltech/Config
)
