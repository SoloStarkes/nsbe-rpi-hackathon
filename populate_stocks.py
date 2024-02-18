import sqlite3, config, json
import alpaca_trade_api as tradeapi
connection = sqlite3.connect('app.db')

# Organize rows as dictionaries
connection.row_factory = sqlite3.Row

cursor = connection.cursor()

# list all the stocks from the stock table
cursor.execute("""
    SELECT symbol, company FROM stock
""")
rows = cursor.fetchall()
symbols = [row['symbol'] for row in rows]

api = tradeapi.REST(config.API_KEY, config.SECRET_API_KEY,
                    base_url=config.BASE_URL)

# List all the stocks available in Alpaca API
assets = api.list_assets()

for asset in assets:
    # Checks for new stocks and adds them to the database every time the script is run
    try:
        if asset.status == 'active' and asset.tradable and asset.symbol not in symbols:
            print(f"Added {asset.symbol} > {asset.name} to the database")
            cursor.execute(
                "INSERT INTO stock (symbol, name) VALUES (?,?)", (asset.symbol, asset.name))
    
    except Exception as e:
        print(f"Could not add {asset.symbol} to the database")
        print(e)

connection.commit()