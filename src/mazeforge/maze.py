# -*- coding: utf-8 -*-
from mazeforge.core.loader import generate_maze, print_maze


class Maze:
    def __init__(self, width, height):
        self.array = [-1] * width * height

    def print(self):
        print_maze(self.array, self.width, self.height)

    def generate(self):
        generate_maze(self.array, self.width, self.height)