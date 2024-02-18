import config
import alpaca_trade_api as tradeapi
from alpaca_trade_api.rest import REST, TimeFrame

api = tradeapi.REST(config.API_KEY, config.SECRET_API_KEY, base_url=config.BASE_URL)

barsets = api.get_bars(['AAPL', 'MSFT'], TimeFrame.Day, "2024-02-14")

print("#############################")
print(barsets)
print(type(barsets))
print("#############################")

for symbol in barsets:
    print(f"Symbol: {symbol}")
    for bar in barsets:
        print(f"Time: {bar.t} Open: {bar.o} High: {bar.h} Low: {bar.l} Close: {bar.c} Volume: {bar.v}")