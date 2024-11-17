import pygame

from block_decorator import BlockDecorator


class ColoredBlockDecorator(BlockDecorator):
    def __init__(self, block, color):
        super().__init__(block)
        self.color = color

    def draw(self, screen, offset_x, offset_y):
        tiles = self.get_cell_positions()
        for tile in tiles:
            tile_rect = pygame.Rect(offset_x + tile.column * self.cell_size,
                                    offset_y + tile.row * self.cell_size, self.cell_size - 1, self.cell_size - 1)
            pygame.draw.rect(screen, self.color, tile_rect)
