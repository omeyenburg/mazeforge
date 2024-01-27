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


mazeforge_util.c_print.argtypes = []
mazeforge_util.c_print.restype = None

"""
0:


1:
  │

  
2:

──

3:
  │
──┘
"""

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


def array(*args):
    return (ctypes.c_uint8 * len(args))(*args)


"""
mazeforge_util.print_maze.argtypes = [ctypes.POINTER(ctypes.POINTER(ctypes.c_int)), ctypes.c_int, ctypes.c_int]
mazeforge_util.print_maze.restype = None

rows = 3
cols = 4

# Create a 2D NumPy array
myArray = np.arange(rows * cols, dtype=np.int32).reshape((rows, cols))

# Convert the NumPy array to a pointer to pointer
array_pointer = (ctypes.POINTER(ctypes.c_int) * rows)()
for i in range(rows):
    array_pointer[i] = myArray[i].ctypes.data_as(ctypes.POINTER(ctypes.c_int))

# Call the C function
mazeforge_util.print_maze(array_pointer, rows, cols)
"""


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