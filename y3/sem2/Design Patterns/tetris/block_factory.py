from blocks import *

class BlockFactory:
    @staticmethod
    def create_block(block_id):
        if block_id == 1:
            return LBlock()
        elif block_id == 2:
            return JBlock()
        elif block_id == 3:
            return IBlock()
        elif block_id == 4:
            return OBlock()
        elif block_id == 5:
            return SBlock()
        elif block_id == 6:
            return TBlock()
        elif block_id == 7:
            return ZBlock()
        else:
            raise ValueError("Invalid block ID")