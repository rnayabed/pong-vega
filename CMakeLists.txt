cmake_minimum_required(VERSION 3.5)

set(RISCV_ARCH rv32im)
set(RISCV_ABI ilp32)
set(RISCV_CMODEL medany)

if (NOT RISCV_TOOLCHAIN_FULL_PATH)
    set(RISCV_TOOLCHAIN_FULL_PATH riscv64-unknown-elf)
endif()

set(CMAKE_SYSTEM_NAME               Generic)
set(CMAKE_SYSTEM_PROCESSOR          riscv)
set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)

set(CMAKE_AR                        ${RISCV_TOOLCHAIN_FULL_PATH}-ar${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_ASM_COMPILER              ${RISCV_TOOLCHAIN_FULL_PATH}-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_C_COMPILER                ${RISCV_TOOLCHAIN_FULL_PATH}-gcc${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_CXX_COMPILER              ${RISCV_TOOLCHAIN_FULL_PATH}-g++${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_LINKER                    ${RISCV_TOOLCHAIN_FULL_PATH}-ld${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_OBJCOPY                   ${RISCV_TOOLCHAIN_FULL_PATH}-objcopy${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_RANLIB                    ${RISCV_TOOLCHAIN_FULL_PATH}-ranlib${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_SIZE                      ${RISCV_TOOLCHAIN_FULL_PATH}-size${CMAKE_EXECUTABLE_SUFFIX})
set(CMAKE_STRIP                     ${RISCV_TOOLCHAIN_FULL_PATH}-strip${CMAKE_EXECUTABLE_SUFFIX})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(pong-vega LANGUAGES C ASM)

add_executable(${PROJECT_NAME}
    config.h
    crt.S
    display.h display.c
    timer.h timer.c
    gpio.h
    main.c
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -T${CMAKE_SOURCE_DIR}/common/mbl.lds
    -march=${RISCV_ARCH} -mabi=${RISCV_ABI} -mcmodel=${RISCV_CMODEL}
    -fno-lto
    -nostartfiles
    -fdata-sections -ffunction-sections
    -fno-tree-loop-distribute-patterns
    -ffreestanding
    -nostdlib
)

target_link_options(${PROJECT_NAME}  PUBLIC
    -T${CMAKE_SOURCE_DIR}/link.lds
    -nostdlib
    -march=${RISCV_ARCH} -mabi=${RISCV_ABI} -mcmodel=${RISCV_CMODEL}
    -Wl,--gc-sections -Wl,-Map=taurus.map
    -fno-lto
    -nostartfiles
    -fdata-sections -ffunction-sections
    -fno-tree-loop-distribute-patterns
    -ffreestanding
    -s
)

