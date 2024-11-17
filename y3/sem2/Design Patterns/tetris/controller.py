import pygame
from game_facade import GameFacade

pygame.init()
screen = pygame.display.set_mode((500, 620))
pygame.display.set_caption("Python Tetris")

facade = GameFacade()
facade.start_game()
