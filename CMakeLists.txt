cmake_minimum_required(VERSION 3.17)

project(ctf_gen)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(BARECTF_ROOT ${CMAKE_BINARY_DIR}/deps/barectf)
set(BARECTF_TEST ${CMAKE_SOURCE_DIR}/barectf_test)
set(BARECTF_GEN ${BARECTF_TEST}/gen)
set(BARECTF_OUTPUT "${BARECTF_GEN}/src/barectf.c")

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/barectf_test/gen)
file(MAKE_DIRECTORY ${BARECTF_GEN}/include)
file(MAKE_DIRECTORY ${BARECTF_GEN}/src)
file(MAKE_DIRECTORY ${BARECTF_GEN}/traces)

FetchContent_Declare(
        barectf_external
        GIT_REPOSITORY https://github.com/efficios/barectf.git
)

FetchContent_MakeAvailable(barectf_external)

include_directories(ctf_gen PRIVATE ${BARECTF_GEN}/include ${barectf_external_SOURCE_DIR})

add_executable(ctf_gen
        barectf_test/src/main.cpp
        ${BARECTF_OUTPUT}
        ${barectf_external_SOURCE_DIR}/platforms/linux-fs/barectf-platform-linux-fs.c
        )

add_custom_command(
        OUTPUT ${BARECTF_OUTPUT}
        COMMAND barectf gen -H ${BARECTF_GEN}/include -c ${BARECTF_GEN}/src -m ${BARECTF_GEN}/traces ${BARECTF_TEST}/config/config.yaml
        COMMENT "Generate sources with barectf"
)
