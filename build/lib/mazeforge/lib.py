# -*- coding: utf-8 -*-
import platform
import ctypes
import os


def load_library():
    system = platform.system()
    machine = platform.machine()

    library_path = None
    cwd = os.path.dirname(os.path.abspath(__file__))

    if system == "Linux":
        if "x86_64" in machine:
            library_path = "lib/linux/x86_64/libmazeforgeutil.so"
        elif "i686" in machine:
            library_path = "lib/linux/i686/libmazeforgeutil.so"
        elif "arm" in machine:
            library_path = "lib/linux/arm/libmazeforgeutil.so"
        elif "aarch64" in machine:
            library_path = "lib/linux/aarch64/libmazeforgeutil.so"
    elif system == "Darwin":
        if "x86_64" in machine:
            library_path = "lib/macos/x86_64/libmazeforgeutil.dylib"
        else:
            library_path = "lib/macos/arm/libmazeforgeutil.dylib"
    elif system == "Windows":
        if "AMD64" in machine or "x86_64" in machine:
            library_path = "lib/windows/x86_64/libmazeforgeutil.dll"
        else:
            library_path = "lib/windows/i686/libmazeforgeutil.dll"

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
configure_library(mazeforge_util)


"""
# Function prototypes
graphics.c_init.argtypes = [ctypes.c_int, ctypes.c_int]
graphics.c_init.restype = ctypes.c_int

graphics.c_update.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int)]
graphics.c_update.restype = ctypes.POINTER(ctypes.c_uint8)

graphics.c_quit.argtypes = []
graphics.c_quit.restype = None

graphics.c_info_max_tex_size = []
graphics.c_info_max_tex_size = ctypes.c_int

graphics.c_load_shader.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.POINTER(ctypes.c_char_p), ctypes.POINTER(ctypes.c_char_p), ctypes.c_int]
graphics.c_load_shader.restype = ctypes.c_int
graphics.load_shader = lambda vertex, fragment, **variables: graphics.c_load_shader(
    vertex.encode("utf-8"), fragment.encode("utf-8"),
    (ctypes.c_char_p * len(variables))(*map(lambda v: v.encode("utf-8"), variables.keys())),
    (ctypes.c_char_p * len(variables))(*map(lambda v: v.encode("utf-8"), variables.values())),
    len(variables))

graphics.c_update_shader_value.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_void_p]
graphics.c_update_shader_value.restype = None
def p_update_shader_value(shader, index, value):
    if isinstance(value, int):
        c_value = ctypes.c_int(value)
    elif isinstance(value, float):
        c_value = ctypes.c_float(value)
    elif isinstance(value, (list, tuple)):
        if isinstance(value[0], int):
            c_value = (ctypes.c_int * len(value))(*value)
        elif isinstance(value[0], float):
            c_value = (ctypes.c_float * len(value))(*value)
    else:
        raise ValueError("Invalid value %r" % value)
    graphics.c_update_shader_value(shader, index, ctypes.byref(c_value))
graphics.update_shader_value = p_update_shader_value

graphics.activate_shader.argtypes = [ctypes.c_int]
graphics.activate_shader.restype = None

"""