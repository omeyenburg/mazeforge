import random
import numpy

def generate(width: int, height: int) -> numpy.array:
    width = width * 2 + 1
    height = height * 2 + 1
    maze = numpy.ones((width, height))

    for x, y in numpy.ndindex((width, height)):
        if 1 == x % 2 == y % 2:
            maze[x, y] = 0

    # Prim's algorithm
    maze_width = (width - 1) // 2
    maze_height = (height - 1) // 2


    def get_neighbours(x, y):
        neighbours = {(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)}
        for neighbour in tuple(neighbours):
            if not (0 <= neighbour[0] < maze_width and 0 <= neighbour[1] < maze_height):
                neighbours.discard(neighbour)
        return neighbours


    existing_cells = {(maze_width // 2, maze_height // 2)}
    adjacent_cells = get_neighbours(*list(existing_cells)[0])

    while len(adjacent_cells):
        new_cell = random.choice(tuple(adjacent_cells))
        neighbours = get_neighbours(*new_cell)
        existing_neigbours = neighbours.intersection(existing_cells)
        new_neighbours = neighbours.difference(existing_cells)

        connection = random.choice(tuple(existing_neigbours))
        existing_cells.add(new_cell)
        adjacent_cells |= new_neighbours
        adjacent_cells.discard(new_cell)
        
        x = (new_cell[0] * 2 + 1 + connection[0] * 2 + 1) // 2
        y = (new_cell[1] * 2 + 1 + connection[1] * 2 + 1) // 2
        maze[x, y] = 0

    return maze