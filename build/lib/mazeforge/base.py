import numpy


class Maze(numpy.ndarray):
    def __new__(cls, width, height):
        # Create a new array with the specified dimensions and fill value
        maze_array = numpy.full((height, width), 0, dtype=numpy.int_)
        obj = maze_array.view(cls)
        return obj

    @classmethod
    def from_array(cls, array):
        """
        Create a new Maze instance from an existing NumPy array
        """
        return array.view(cls)