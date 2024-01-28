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
    

def configure_library(lib):
    lib.c_print.argtypes = []
    lib.c_print.restype = None


mazeforge_util = load_library()
mazeforge_util.init.argtypes = []
mazeforge_util.init.restype = None
mazeforge_util.init()
mazeforge_util.test.argtypes = []
mazeforge_util.test.restype = None

# print_maze
mazeforge_util.print_maze.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_int,
    ctypes.c_int
]
mazeforge_util.print_maze.restype = None
print_maze = lambda array, width, height: mazeforge_util.print_maze(
    (ctypes.c_uint8 * (width * height))(*array),
    width,
    height
)

# generate_maze
mazeforge_util.generate_maze.argtypes = [
    ctypes.POINTER(ctypes.c_uint8),
    ctypes.c_int,
    ctypes.c_int
]
mazeforge_util.generate_maze.restype = None
generate_maze = lambda array, width, height: mazeforge_util.generate_maze(
    (ctypes.c_uint8 * (width * height))(*array),
    width,
    height
)

