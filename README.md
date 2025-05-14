# MazeForge
Generation of mazes for Python.<br>
Written in C, because i need a maze real quick!

MazeForge is supported on Python 3.7 and above.

## Documentation
### Generating a maze
This generates a perfect maze, which means that any two cells are connected by one single unique path.<br>
The maze is generated using the prim's algorithm.

```python
>>> from mazeforge import Maze
>>> Maze(width=5, height=5)
Maze(width=5, height=5)
```

### Pretty-printing a maze
You can print the Maze using the print method.

```python
>>> from mazeforge import Maze
>>> Maze(5, 5).print()
┌───────┬───────────┐   
│       │           │   
├───╴   └───╴   ╷   │   
│               │   │   
│   ┌───────╴   ├───┤   
│   │           │   │   
├───┘   ╷   ╷   ╵   │   
│       │   │       │   
├───────┘   │   ╷   │   
│           │   │   │   
└───────────┴───┴───┘
```

For further use, you may also convert the maze into a string.

```python
>>> from mazeforge import Maze
>>> maze = Maze(5, 5)
>>> str(maze)
'┌───────┬───────────┐   \n│       │           │   \n├───╴   └───╴   ╷   │   \n│               │   │   \n│   ┌───────╴   ├───┤   \n│   │           │   │   \n├───┘   ╷   ╷   ╵   │   \n│       │   │       │   \n├───────┘   │   ╷   │   \n│           │   │   │   \n└───────────┴───┴───┘'
```
