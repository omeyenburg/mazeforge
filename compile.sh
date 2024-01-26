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
COMPILER_WARNINGS="-w" # Default: -Wall

GCC_LINUX_x86_64="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_LINUX_i686="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_LINUX_ARM="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_LINUX_AArch64="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_MACOS_x86_64="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_MACOS_ARM="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_WINDOWS_x86_64="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"
GCC_WINDOWS_i686="/usr/local/bin/x86_64-unknown-linux-gnu-gcc"

COMPILERS=(
    ${GCC_LINUX_x86_64}
    ${GCC_LINUX_i686}
    ${GCC_LINUX_ARM}
    ${GCC_LINUX_AArch64}
    ${GCC_MACOS_x86_64}
    ${GCC_MACOS_ARM}
    ${GCC_WINDOWS_x86_64}
    ${GCC_WINDOWS_i686}
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
echo Done

exit 0



# Create output directories
mkdir -p ${DIR_OUT}/linux/x86_64
mkdir -p ${DIR_OUT}/linux/i686
mkdir -p ${DIR_OUT}/linux/arm
mkdir -p ${DIR_OUT}/linux/aarch64
mkdir -p ${DIR_OUT}/macos/x86_64
mkdir -p ${DIR_OUT}/macos/arm
mkdir -p ${DIR_OUT}/windows/x86_64
mkdir -p ${DIR_OUT}/windows/i686

# Linux:
# x86, 64-bit
echo Compiling for linux-x86_64
#/usr/local/bin/x86_64-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/x86_64/lib${LIB_NAME}.so
compiler=${COMPILERS[0]}
${COMPILERS[0]} $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
${COMPILERS[0]} $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
${COMPILERS[0]} -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# x86, 32-bit
echo Compiling for linux-i686
#/usr/local/bin/i686-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/i686/lib${LIB_NAME}.so
$GCC_LINUX_i686 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_LINUX_i686 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_LINUX_i686 -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# ARM
echo Compiling for linux-arm
#/usr/local/bin/arm-unknown-linux-gnueabi-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/arm/lib${LIB_NAME}.so
$GCC_LINUX_ARM $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_LINUX_ARM $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_LINUX_ARM -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# AArch64
echo Compiling for linux-aarch64
#/usr/local/bin/aarch64-unknown-linux-gnu-gcc main.c -shared -fPIC -o ${DIR_OUT}/linux/aarch64/lib${LIB_NAME}.so
$GCC_LINUX_AArch64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_LINUX_AArch64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_LINUX_AArch64 -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# macOS:
# x86_64
echo Compiling for macos-x86_64
#/usr/local/bin/x86_64-apple-darwin19-gcc-12 main.c -shared -fPIC -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib
$GCC_MACOS_x86_64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_MACOS_x86_64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_MACOS_x86_64 -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# ARM
echo Compiling for macos-arm
#/usr/local/bin/arm-none-eabi-gcc main.c -shared -fPIC -o ${DIR_OUT}/macos/arm/lib${LIB_NAME}.dylib
$GCC_MACOS_ARM $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_MACOS_ARM $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_MACOS_ARM -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# Windows:
# x86_64-pc-windows-gnu (GNU toolchain, 64-bit)
echo Compiling for windows-x86_64
#/usr/local/bin/x86_64-w64-mingw32-gcc main.c -shared -fPIC -o ${DIR_OUT}/windows/x86_64/${LIB_NAME}.dll
$GCC_WINDOWS_x86_64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_WINDOWS_x86_64 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_WINDOWS_x86_64 -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

# i686-pc-windows-gnu (GNU toolchain, 32-bit)
echo Compiling for windows-i686
#/usr/local/bin/i686-w64-mingw32-gcc main.c -shared -fPIC -o ${DIR_OUT}/windows/i686/${LIB_NAME}.dll
$GCC_WINDOWS_i686 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/generator.c -o ${DIR_SOURCE}/generator.o
$GCC_WINDOWS_i686 $COMPILER_WARNINGS -fPIC -c ${DIR_SOURCE}/bst.c -o ${DIR_SOURCE}/bst.o
$GCC_WINDOWS_i686 -shared -o ${DIR_OUT}/macos/x86_64/lib${LIB_NAME}.dylib ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o

rm ${DIR_SOURCE}/generator.o ${DIR_SOURCE}/bst.o
echo Done