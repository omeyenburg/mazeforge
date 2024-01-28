# -*- coding: utf-8 -*-
from .core.loader import generator
import ctypes

"""
class Maze:
    def __init__(self, width, height):
        self.array = [0] * width * height
        self.width = width
        self.height = height

    def print(self):
        print_maze(self.array, self.width, self.height)

    def generate(self):
        generate_maze(self.array, self.width, self.height)
"""

def generate(width, height):
    """
    Generate a 2d maze on a grid.
    The maze is printed into the console. This will change in future versions.
    
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
    array = [0] * width * height
    array = (ctypes.c_uint8 * (width * height))(*array)
    generator.generate_maze(array, width, height)
    #return [array[i * width + j] for i in range(height) for j in range(width)]