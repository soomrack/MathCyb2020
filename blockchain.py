from block import Block
from transaction import Transaction
from pyllist import sllist


class Blockchain:
    __TARGET_BITS = 4

    def __init__(self):
        """Initialize blockchain"""

        genesys_block = self.__mine(Block([Transaction("")], self.__valid_block_start()))
        self.__chain = sllist([genesys_block])

    def add_transaction(self, transaction):
        block = self.__mine(Block([transaction], self.__last_block().value.hash()))
        self.__chain.appendleft(block)

    def save_to_file(self, filename):
        file = open(filename, 'w')
        current_block = self.__last_block()
        while (current_block != None):
            file.write('block:\n')
            current_block.value.save_to_file(file)
            current_block = current_block.next
        file.close()

    def load_from_file(self, filename):
        pass

    def print_blocks_data(self, n=0):
        """print all blocks data if n equal 0"""

        if n <= 0 or n >= self.__chain.size:
            n = self.__chain.size - 1

        current_block = self.__last_block()
        for _ in range(n):
            print(current_block.value.data())
            current_block = current_block.next
        return n

    def __mine(self, block):
        while not self.__validation(block):
            block.nonce += 1
        return block

    def __validation(self, block):
        return block.hash()[:self.__TARGET_BITS] == self.__valid_block_start()

    def __valid_block_start(self):
        return '0' * self.__TARGET_BITS

    def __last_block(self):
        return self.__chain.first