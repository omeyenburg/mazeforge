# MazeForge

Generation of mazes in Python

## Installation

You can install **MazeForge** from [PyPI](https://pypi.org/project/mazeforge/) by running the following in your terminal.<br>
`python -m pip install mazeforge`
<br>

MazeForge is supported on Python 3.7 and above.

## How to use

```python
>>> import mazeforge
>>> mazeforge.generate(3, 3)
array([[1., 1., 1., 1., 1., 1., 1.],
       [1., 0., 1., 0., 0., 0., 1.],
       [1., 0., 1., 0., 1., 1., 1.],
       [1., 0., 0., 0., 1., 0., 1.],
       [1., 1., 1., 0., 1., 0., 1.],
       [1., 0., 0., 0., 0., 0., 1.],
       [1., 1., 1., 1., 1., 1., 1.]])
```

## Documentation

### mazeforge.generate

`mazeforge.generate` generates a perfect maze. This means that any two cells are connected by one single unique path. The function returns 2d numpy array. Walls are represented as a `1` and corridor as a `0`. The maze is generated using the prim's algorithm.
