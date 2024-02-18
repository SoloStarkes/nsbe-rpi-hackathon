import sqlite3, config
import alpaca_trade_api as tradeapi

connection = sqlite3.connect('app.db')
connection.row_factory = sqlite3.Row # Make the rows returned by the cursor be dictionaries instead of tuples

# Create a cursor (an object that can execute commands)
cursor = connection.cursor()

cursor.execute('''
    SELECT symbol, company FROM stock
''')

rows = cursor.fetchall() 
symbols = [row['symbol'] for row in rows]
# print(symbols)

# Insert some data into the stock table manually
# cursor.execute("INSERT INTO stock (symbol, company) VALUES ('AAPL', 'Apple Inc.')")
# cursor.execute("INSERT INTO stock (symbol, company) VALUES ('GOOGL', 'Alphabet Inc.')")
# cursor.execute("INSERT INTO stock (symbol, company) VALUES ('MSFT', 'Microsoft Corporation')")

# cursor.execute("DELETE FROM stock")

# API ACCESS TO POPULATE THE DATABASE
api = tradeapi.REST(config.API_KEY, config.SECRET_API_KEY, base_url=config.BASE_URL)
assets = api.list_assets()

for asset in assets:
    # Checks for new stocks and adds them to the database every time the script is run
    try:
        if asset.symbol not in symbols and asset.status == 'active' and asset.tradable:
            cursor.execute("INSERT INTO stock (symbol, company) VALUES (?, ?)", (asset.symbol, asset.name))
            print(f"Added {asset.symbol} > {asset.name} to the database")

    except Exception as e:
        print(f"Could not add {asset.symbol} to the database")
        print(e)

# Insert data into the stock table using a file
# for line in open('nasdaq.txt'):
#     data = line.strip().split('|')
#     symbol = data[0]
#     company = data[1]
#     cursor.execute("INSERT INTO stock (symbol, company) VALUES (?, ?)", (symbol, company))
#     print(symbol, company)

# Commit the changes
connection.commit()