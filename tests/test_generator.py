import src.mazeforge as mazeforge
# import pygame
import numpy
import time

width = height = 4
maze = mazeforge.generate(width, height)
print(maze)
time.sleep(1)
# width = width * 2 + 1
# height = height * 2 + 1
# pygame.init()
# window = pygame.display.set_mode((width * 10, height * 10))


# for x, y in numpy.ndindex((width, height)):
#     if not maze[x, y]:
#         pygame.draw.rect(window, (255, 255, 255), (x * 10, y * 10, 10, 10))


# while True:
#     for event in pygame.event.get():
#         if event.type == pygame.QUIT:
#             pygame.quit()
#             raise SystemExit()

#     pygame.display.flip()