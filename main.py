from blockchain import Blockchain, Transaction

chain = Blockchain()
chain.add_transaction(Transaction("first block message"))
chain.print_blocks_data()
chain.add_transaction(Transaction("second block message"))
chain.print_blocks_data(1)
chain.save_to_file('chain')