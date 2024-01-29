# -*- coding: utf-8 -*-
from .core.loader import generator
import ctypes

class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.array = generate(width, height)

    def __repr__(self):
        return f"Maze(width: {self.width}, {self.height})"

    def __str__(self):
        string = maze_string(self.array, self.width, self.height)
        return string
    
    def print(self):
        print(maze_string(self.array, self.width, self.height))


def generate(width, height):
    """
    Generate a 2d maze on a grid.
    
    Parameters
    ----------
    width : int
        Number of columns in the maze.
    height : int
        Number of rows in the maze.

    Returns
    -------
    list[int]
        Internal list representation of the maze.
    """
    SIZE = width * height

    array = [0] * SIZE
    array = (ctypes.c_uint8 * (SIZE))(*array)
    generator.generate_maze(array, width, height)

    return tuple(array)

def maze_string(array, width, height):
    SYMBOLS = ("  ", "╶─", "╷ ", "┌─", "╴ ", "──", "┐ ", "┬─", "╵ ", "└─", "│ ", "├─", "┘ ", "┴─", "┤ ", "┼─", "\n")
    SIZE = (width * 2 + 3) * (height * 2 + 1)

    chars = (ctypes.c_uint8 * SIZE)(*([0] * SIZE))
    array = (ctypes.c_uint8 * (width * height))(*array)
    generator.print_maze(array, chars, width, height)

    string = "".join(map(SYMBOLS.__getitem__, tuple(chars)))
    return string[:-1]