class Transaction:

    def __init__(self, message):
        self.__message = message

    def data(self):
        return self.__message

    def save_to_file(self, file):
        file.write('message: {}\n'.format(self.__message))
