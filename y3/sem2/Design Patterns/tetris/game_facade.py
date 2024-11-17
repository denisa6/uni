import pygame
import sys

from game import Game
from view import GameView
from game_state import *

class GameFacade:
    def __init__(self):
        self.game = None
        self.game_view = None
        self.state = None

    def change_state(self, new_state):
        self.state = new_state

    def start_game(self):
        self.game = Game(score=10, target_score=100)

        # Create the game view
        self.game_view = GameView(pygame.display.get_surface(), self.game)
        # Set initial game state
        self.state = PlayingState()
        # Start the game loop
        self._start_game_loop(self.game)

    def _start_game_loop(self, game):
        clock = pygame.time.Clock()
        GAME_UPDATE = pygame.USEREVENT
        pygame.time.set_timer(GAME_UPDATE, 200)

        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                # Delegate event handling to the current state
                self.state.handle_event(event, game, self)

            # Update the game state
                if event.type == GAME_UPDATE and not game.game_over:
                    self.state.update(game)
            # Draw the game view
            self.state.draw(self.game_view)

            clock.tick(60)
