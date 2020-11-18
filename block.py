from datetime import datetime
from hashlib import sha256


class Block:

    def __init__(self, transactions, previous_hash, nonce=0, timestamp=datetime.utcnow()):
        """Initialize block"""

        self.__transactions = transactions
        self.__previous_hash = previous_hash
        self.__nonce = nonce
        self.__timestamp = timestamp

    def data(self):
        data = []
        for transaction in self.__transactions:
            data.append(transaction.data())
        return data

    def hash(self):
        return sha256(self.__block_str().encode()).hexdigest()

    def save_to_file(self, file):
        for transaction in self.__transactions:
            transaction.save_to_file(file)
        file.write('previous_hash: {}\nnonce: {}\ntimestamp: {}\n'.format(self.__previous_hash, self.__nonce, self.__timestamp))

    def __block_str(self):
        return '{}{}{}{}'.format(self.data(), self.__previous_hash, self.__nonce, self.__timestamp)

    @property
    def previous_hash(self):
        return self.__previous_hash

    @property
    def nonce(self):
        return self.__nonce

    @nonce.setter
    def nonce(self, nonce):
        self.__nonce = nonce
