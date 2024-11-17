from block import Block


class BlockDecorator(Block):
    def __init__(self, block):
        super().__init__(block.id)
        self.block = block

    def move(self, rows, columns):
        self.block.move(rows, columns)

    def get_cell_positions(self):
        return self.block.get_cell_positions()

    def rotate(self):
        self.block.rotate()

    def undo_rotation(self):
        self.block.undo_rotation()

    def draw(self, screen, offset_x, offset_y):
        self.block.draw(screen, offset_x, offset_y)
