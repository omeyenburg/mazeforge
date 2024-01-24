#!/bin/bash
# Install windows compilers with `brew install mingw-w64`
# Install linux compilers with `brew install filosottile/musl-cross/musl-cross`
# Install more linux compilers from https://github.com/messense/homebrew-macos-cross-toolchains
# Install mac compiler for m1 with `brew install armmbed/formulae/arm-none-eabi-gcc`
cd $(dirname $0)

mkdir -p lib/linux/x86_64
mkdir -p lib/linux/i686
mkdir -p lib/linux/arm
mkdir -p lib/linux/aarch64
mkdir -p lib/macos/x86_64
mkdir -p lib/macos/arm
mkdir -p lib/windows/x86_64
mkdir -p lib/windows/i686

# Linux:
# x86, 64-bit
/usr/local/bin/x86_64-unknown-linux-gnu-gcc main.c -shared -fPIC -o lib/linux/x86_64/libmazeforgeutil.so

# x86, 32-bit
/usr/local/bin/i686-unknown-linux-gnu-gcc main.c -shared -fPIC -o lib/linux/i686/libmazeforgeutil.so

# ARM
/usr/local/bin/arm-unknown-linux-gnueabi-gcc main.c -shared -fPIC -o lib/linux/arm/libmazeforgeutil.so

# AArch64
/usr/local/bin/aarch64-unknown-linux-gnu-gcc main.c -shared -fPIC -o lib/linux/aarch64/libmazeforgeutil.so

# macOS:
# x86_64
/usr/local/bin/x86_64-apple-darwin19-gcc-12 main.c -shared -fPIC -o lib/macos/x86_64/libmazeforgeutil.dylib

# ARM
/usr/local/bin/arm-none-eabi-gcc main.c -shared -fPIC -o lib/macos/arm/libmazeforgeutil.dylib

# Windows:
# x86_64-pc-windows-gnu (GNU toolchain, 64-bit)
/usr/local/bin/x86_64-w64-mingw32-gcc main.c -shared -fPIC -o lib/windows/x86_64/libmazeforgeutil.dll

# i686-pc-windows-gnu (GNU toolchain, 32-bit)
/usr/local/bin/i686-w64-mingw32-gcc main.c -shared -fPIC -o lib/windows/i686/libmazeforgeutil.dll
