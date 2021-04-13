cmake_minimum_required(VERSION 3.17)

project(ctf_gen)

set(CMAKE_CXX_STANDARD 20)

include(ExternalProject)

set(BARECTF_ROOT ${CMAKE_BINARY_DIR}/deps/barectf)
set(BARECTF_TEST ${CMAKE_SOURCE_DIR}/barectf_test)
set(BARECTF_GEN ${BARECTF_TEST}/gen)

ExternalProject_Add(barectf_external
        PREFIX ${BARECTF_ROOT}
        GIT_REPOSITORY "https://github.com/efficios/barectf.git"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        )

ExternalProject_Get_Property(barectf_external source_dir)
set(BareCtfIncludeDir ${source_dir})

include_directories(ctf_gen PRIVATE ${BareCtfIncludeDir} ${BARECTF_GEN}/include)

file(GLOB BARECTF_GEN_SRC ${BARECTF_GEN}/src/*.c)

add_executable(ctf_gen
        barectf_test/src/main.cpp
        ${BARECTF_GEN_SRC}
        ${BareCtfIncludeDir}/platforms/linux-fs/barectf-platform-linux-fs.c
        )

add_custom_target(
        run ALL
        COMMAND barectf gen -H ${BARECTF_GEN}/include -c ${BARECTF_GEN}/src -m ${BARECTF_GEN}/traces ${BARECTF_TEST}/config/config.yaml
        BYPRODUCTS barectf.h
        COMMENT "Generate sources with barectf"
)

add_dependencies(ctf_gen run barectf_external)

