# Linux:

# x86_64-unknown-linux-gnu (64-bit)
# i686-unknown-linux-gnu (32-bit)
# macOS:

# x86_64-apple-darwin
# Windows:

# x86_64-pc-windows-msvc (MSVC toolchain, 64-bit)
# i686-pc-windows-msvc (MSVC toolchain, 32-bit)
# x86_64-pc-windows-gnu (GNU toolchain, 64-bit)
# i686-pc-windows-gnu (GNU toolchain, 32-bit)
# BSD:

# x86_64-unknown-freebsd (FreeBSD, 64-bit)
# i686-unknown-freebsd (FreeBSD, 32-bit)
# x86_64-unknown-netbsd (NetBSD, 64-bit)
# i686-unknown-netbsd (NetBSD, 32-bit)
# Others:

# aarch64-unknown-linux-gnu (ARM 64-bit, Linux)
# armv7-unknown-linux-gnueabihf (ARM 32-bit, Linux with hard-float ABI)
# wasm32-unknown-unknown (WebAssembly)

# my_python_module.py
from ctypes import cdll
import platform

arch = platform.architecture()[0]
lib_name = f"target/release/libmy_rust_project.so" if arch == "64bit" else f"target/release/libmy_rust_project.so"

# Load the compiled Rust module
rust_module = cdll.LoadLibrary(lib_name)

# Define the Python interface to the Rust function
def add_numbers(a, b):
    return rust_module.add_numbers(a, b)

