# meanReversionAlgorithm
A simple mean reversion algorithm testing buying or selling an asset

This is a simple implementation of a mean reversion algorithm.
The program reads performs 4 main steps:
1) It reads in the latest price for the current day and adds to our vector of prices
2) It then calculates the average of the previous X days' prices (X is specified when calling function)
3) If the current price is lower below a certaint threshold, it buys a single of the asset.
   Likewise if the price is above a certain threshold, it sells a single unit of the asset.
   These are calculated here based on percentages above/below the rolling average
4) The current profit is reupdated

For testing purposes, a sample of share prices from Yahoo finance are in the GOOGL1.csv file.

Note the function is not very effective on the whole, based on the very basic buying/selling decisions.
The aim is now to improve the actual decision making algorithm given I have a framework to test it
