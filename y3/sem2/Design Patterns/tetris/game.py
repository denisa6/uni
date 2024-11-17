from block_factory import BlockFactory
from blocks import *
import random

from colored_block_decorator import ColoredBlockDecorator
from colors import Colors
from model import Grid


class Game:
    def __init__(self, game_over=False, score=0, target_score=-1):
        self.grid = Grid()
        self.game_over = game_over
        self.game_win = False
        self.score = score
        self.current_block = None
        self.next_block = None
        self.target_score = target_score
        self.blocks = [IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()]
        self.current_block = BlockFactory.create_block(random.randint(1, 7))
        self.next_block = BlockFactory.create_block(random.randint(1, 7))

    def update_score(self, lines_cleared, move_down_points):
        if lines_cleared == 1:
            self.score += 100
        elif lines_cleared == 2:
            self.score += 300
        elif lines_cleared == 3:
            self.score += 500
        self.score += move_down_points
        if self.target_score != -1:
            if self.game_over != True and self.score >= self.target_score:
                self.game_win = True

    def get_random_block(self):
        return BlockFactory.create_block(random.randint(1, 7))

    def move_left(self):
        self.current_block.move(0, -1)
        if self.block_inside() == False or self.block_fits() == False:
            self.current_block.move(0, 1)

    def move_right(self):
        self.current_block.move(0, 1)
        if self.block_inside() == False or self.block_fits() == False:
            self.current_block.move(0, -1)

    def move_down(self):
        self.current_block.move(1, 0)
        if self.block_inside() == False or self.block_fits() == False:
            self.current_block.move(-1, 0)
            self.lock_block()

    def lock_block(self):
        tiles = self.current_block.get_cell_positions()
        for position in tiles:
            self.grid.grid[position.row][position.column] = self.current_block.id
        self.current_block = self.next_block
        self.next_block = self.get_random_block()
        rows_cleared = self.grid.clear_full_rows()
        if rows_cleared > 0:
            self.update_score(rows_cleared, 0)
        if self.block_fits() == False:
            self.game_over = True

    def reset(self):
        self.grid.reset()
        self.blocks = [IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()]
        self.current_block = self.get_random_block()
        self.next_block = self.get_random_block()
        self.score = 0

    def block_fits(self):
        tiles = self.current_block.get_cell_positions()
        for tile in tiles:
            if self.grid.is_empty(tile.row, tile.column) == False:
                return False
        return True

    def rotate(self):
        self.current_block.rotate()
        if self.block_inside() == False or self.block_fits() == False:
            self.current_block.undo_rotation()

    def block_inside(self):
        tiles = self.current_block.get_cell_positions()
        for tile in tiles:
            if self.grid.is_inside(tile.row, tile.column) == False:
                return False
        return True

    def draw(self, screen):
        self.grid.draw(screen)
        self.current_block.draw(screen, 11, 11)

        colored_next_block = ColoredBlockDecorator(self.next_block, Colors.dark_grey)

        if self.next_block.id == 3:
            colored_next_block.draw(screen, 255, 290)
        elif self.next_block.id == 4:
            colored_next_block.draw(screen, 255, 280)
        else:
            colored_next_block.draw(screen, 270, 270)
