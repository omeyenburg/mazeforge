import src.mazeforge as mazeforge

def test_generate():
    maze = mazeforge.generate(3, 3)
    print(maze)