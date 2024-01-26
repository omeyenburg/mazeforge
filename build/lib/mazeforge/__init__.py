"""
    MazeForge
    =========

    Provides
      1. Generation of mazes
      2. Solving of mazes
      3. Visualisation of mazes

    Contact
      - oskar.meyenburg@gmail.com

    More information
      - https://pypi.org/project/mazeforge/
      - https://github.com/oskarmeyenburg/mazeforge
"""
from .generator import generate
from .base import Maze
from .core.loader import mazeforge_util


__version__ = "0.1.1"
__all__ = ['Maze', 'generate', 'mazeforge_util']
