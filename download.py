import yfinance

# Apple's full daily stock data from 2020-01-01 to 2020-10-02
df = yfinance.download('AAPL', start='2020-01-01', end='2020-10-02')
df.to_csv('AAPL.csv')