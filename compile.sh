#!/bin/bash
# Install windows compilers with `brew install mingw-w64`
# Install linux compilers with `brew install filosottile/musl-cross/musl-cross`
# Install more linux compilers from https://github.com/messense/homebrew-macos-cross-toolchains
# Install mac compiler for m1 with `brew install armmbed/formulae/arm-none-eabi-gcc`

# Make executable using `chmod +x compile.sh`

DIR_BASE="src/mazeforge/core"
DIR_OUT="platform"
DIR_SOURCE="scripts"
LIB_NAME="maze"
COMPILER_WARNINGS="-Wall" # warnings: "-Wall" | no warnings: "-w"

COMPILERS=(
    "/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
    "/usr/local/bin/i686-unknown-linux-gnu-gcc"
    "/usr/local/bin/arm-unknown-linux-gnueabi-gcc"
    "/usr/local/bin/aarch64-unknown-linux-gnu-gcc"
    "/usr/local/bin/x86_64-apple-darwin19-gcc-12"
    "/usr/local/bin/arm-none-eabi-gcc"
    "/usr/local/bin/x86_64-w64-mingw32-gcc -municode -finput-charset=utf-8"
    "/usr/local/bin/i686-w64-mingw32-gcc -municode -finput-charset=utf-8"
)

OUTPUT_DIRECTORIES=(
    "linux/x86_64"
    "linux/i686"
    "linux/arm"
    "linux/aarch64"
    "macos/x86_64"
    "macos/arm"
    "windows/x86_64"
    "windows/i686"
)

OUTPUT_EXTENSIONS=(
    ".so"
    ".so"
    ".so"
    ".so"
    ".dylib"
    ".dylib"
    ".dll"
    ".dll"
)

# Navigate to c scripts directory
cd $(dirname $0)
cd ${DIR_BASE}

for i in "${!COMPILERS[@]}"; do
    echo Compiling for ${OUTPUT_DIRECTORIES[$i]}
    mkdir -p ${DIR_OUT}/${OUTPUT_DIRECTORIES[$i]}
    ${COMPILERS[$i]} $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
    ${COMPILERS[$i]} $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
    ${COMPILERS[$i]} -shared -o ${DIR_OUT}/${OUTPUT_DIRECTORIES[$i]}/lib${LIB_NAME}${OUTPUT_EXTENSIONS[$i]} ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o
done

rm ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o
echo Compiled
exit 0

# Linux:
# x86, 64-bit
#/usr/local/bin/x86_64-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/x86_64/lib${LIB_NAME}.so

# x86, 32-bit
#/usr/local/bin/i686-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/i686/lib${LIB_NAME}.so

# ARM
#/usr/local/bin/arm-unknown-linux-gnueabi-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/arm/lib${LIB_NAME}.so

# AArch64
#/usr/local/bin/aarch64-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/aarch64/lib${LIB_NAME}.so

# macOS:
# x86_64
#/usr/local/bin/x86_64-apple-darwin19-gcc-12 main.c -shared -fPIC -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib

# ARM
#/usr/local/bin/arm-none-eabi-gcc main.c -shared -fPIC -o ${DIR_OUT}/macos/arm/lib${LIB_NAME}.dylib

# Windows:
# x86_64-pc-windows-gnu (GNU toolchain, 64-bit)
#/usr/local/bin/x86_64-w64-mingw32-gcc main.c -shared -fPIC -o ${DIR_OUT}/windows/x86_64/${LIB_NAME}.dll

# i686-pc-windows-gnu (GNU toolchain, 32-bit)
#/usr/local/bin/i686-w64-mingw32-gcc main.c -shared -fPIC -o ${DIR_OUT}/windows/i686/${LIB_NAME}.dll
