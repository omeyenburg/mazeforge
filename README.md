# MazeForge

Generation of mazes in Python.
MazeForge is supported on Python 3.7 and above.

## Documentation

### class mazeforge.Maze(width, height)

This generates a perfect maze, which means that any two cells are connected by one single unique path. The maze is generated using the prim's algorithm.

```python
>>> import mazeforge
>>> mazeforge.Maze(width=5, height=5)
Maze(width=5, height=5)
```

#### print()

You can print the Maze using the print method.

```python
>>> import mazeforge
>>> mazeforge.Maze(5, 5).print()
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
>>> import mazeforge
>>> maze = mazeforge.Maze(5, 5)
>>> str(maze)
'┌───────┬───────────┐   \n│       │           │   \n├───╴   └───╴   ╷   │   \n│               │   │   \n│   ┌───────╴   ├───┤   \n│   │           │   │   \n├───┘   ╷   ╷   ╵   │   \n│       │   │       │   \n├───────┘   │   ╷   │   \n│           │   │   │   \n└───────────┴───┴───┘'
```
