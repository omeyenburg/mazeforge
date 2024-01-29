# -*- coding: utf-8 -*-
import platform
import ctypes
import os


SHARED_OBJECT_FOLDER = "platform"
SHARED_OBJECT_NAME = "libmaze"


def load_library():
    system = platform.system()
    machine = platform.machine()

    library_path = None
    cwd = os.path.dirname(os.path.abspath(__file__))

    if system == "Linux":
        if "x86_64" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/linux/x86_64/" + SHARED_OBJECT_NAME + ".so"
        elif "i686" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/linux/i686/" + SHARED_OBJECT_NAME + ".so"
        elif "arm" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/linux/arm/" + SHARED_OBJECT_NAME + ".so"
        elif "aarch64" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/linux/aarch64/" + SHARED_OBJECT_NAME + ".so"
    elif system == "Darwin":
        if "x86_64" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/macos/x86_64/" + SHARED_OBJECT_NAME + ".dylib"
        else:
            library_path = SHARED_OBJECT_FOLDER + "/macos/arm/" + SHARED_OBJECT_NAME + ".dylib"
    elif system == "Windows":
        if "AMD64" in machine or "x86_64" in machine:
            library_path = SHARED_OBJECT_FOLDER + "/windows/x86_64/" + SHARED_OBJECT_NAME + ".dll"
        else:
            library_path = SHARED_OBJECT_FOLDER + "/windows/i686/" + SHARED_OBJECT_NAME + ".dll"

    if library_path:
        try:
            return ctypes.CDLL(os.path.join(cwd, library_path))
        except Exception as e:
            raise RuntimeError("Error loading library at {}: {}".format(library_path, e))
    else:
        raise RuntimeError("Unsupported platform: {} {}".format(system, machine))
    

generator = load_library()
generator.init.argtypes = []
generator.init.restype = None
generator.init()
generator.test.argtypes = []
generator.test.restype = None

# print_maze
generator.print_maze.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_int,
    ctypes.c_int
]
generator.generate_maze.restype = ctypes.c_wchar_p


# generate_maze
generator.generate_maze.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_int,
    ctypes.c_int
]
generator.generate_maze.restype = None
