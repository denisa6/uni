import pygame
from colors import Colors


class GameView:
    def __init__(self, screen, game):
        self.screen = screen
        self.game = game
        self.title_font = pygame.font.Font(None, 40)
        self.score_surface = self.title_font.render("Score", True, Colors.white)
        self.next_surface = self.title_font.render("Next", True, Colors.white)
        self.game_over_surface = self.title_font.render("GAME OVER", True, Colors.white)
        self.game_over_win = self.title_font.render("YOU WON", True, Colors.white)
        self.score_rect = pygame.Rect(320, 55, 170, 60)
        self.next_rect = pygame.Rect(320, 215, 170, 180)

    def draw(self):
        score_value_surface = self.title_font.render(str(self.game.score), True, Colors.white)
        self.screen.fill((92, 22, 117))
        self.screen.blit(self.score_surface, (365, 20, 50, 50))
        self.screen.blit(self.next_surface, (375, 180, 50, 50))
        if self.game.game_over:
            self.screen.blit(self.game_over_surface, (320, 450, 50, 50))
        if self.game.game_win:
            self.screen.blit(self.game_over_win, (320, 450, 50, 50))
        pygame.draw.rect(self.screen, (225, 210, 63), self.score_rect, 0, 10)
        self.screen.blit(score_value_surface, score_value_surface.get_rect(centerx=self.score_rect.centerx, centery=self.score_rect.centery))
        pygame.draw.rect(self.screen, (51, 115, 87), self.next_rect, 0, 10)
        self.game.draw(self.screen)
        pygame.display.update()

    def draw_paused(self):
        paused_surface = self.title_font.render("PAUSED", True, Colors.white)
        self.screen.fill((92, 22, 117))
        self.screen.blit(self.score_surface, (365, 20, 50, 50))
        self.screen.blit(self.next_surface, (375, 180, 50, 50))
        pygame.draw.rect(self.screen, (238, 66, 102), self.score_rect, 0, 10)
        score_value_surface = self.title_font.render(str(self.game.score), True, Colors.white)
        self.screen.blit(score_value_surface, score_value_surface.get_rect(centerx=self.score_rect.centerx,
                                                                           centery=self.score_rect.centery))
        pygame.draw.rect(self.screen, (238, 66, 102), self.next_rect, 0, 10)
        self.screen.blit(paused_surface, (100, 200))
        pygame.display.update()
