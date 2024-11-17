import pygame
target_score = 100
class GameState:
    def handle_event(self, event, game, facade):
        raise NotImplementedError()

    def update(self, game):
        raise NotImplementedError()

    def draw(self, game_view):
        raise NotImplementedError()


class PlayingState(GameState):
    def handle_event(self, event, game, facade):
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                facade.change_state(PausedState())
            elif event.key == pygame.K_LEFT:
                game.move_left()
            elif event.key == pygame.K_RIGHT:
                game.move_right()
            elif event.key == pygame.K_DOWN:
                game.move_down()
            elif event.key == pygame.K_UP:
                game.rotate()

    def update(self, game):
        game.move_down()

    def draw(self, game_view):
        game_view.draw()


class PausedState(GameState):
    def handle_event(self, event, game, facade):
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                facade.change_state(PlayingState())

    def update(self, game):
        pass

    def draw(self, game_view):
        game_view.draw_paused()
