// Filename Asset.cpp
// Author: Johnathan Inkley
// Date: 2016 10 26
// Description: Contains definitions for Asset class functions

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Asset.h"

Asset::~Asset()
{
  return;
}

Asset::Asset(const Asset& asset1) : input(asset1.input)
{
  std::vector<double> tempPrices(asset1.prices);
  prices = tempPrices;
  std::vector<double> tempProfits(asset1.profits);
  profits = tempProfits;

  numDays = asset1.numDays;
  buyPrice = asset1.buyPrice;
  sellPrice = asset1.sellPrice;
  avePrice = asset1.avePrice;
  quantity = asset1.quantity;
  currentProfit = asset1.currentProfit;
  currentPrice = asset1.currentPrice;
  currentTime = asset1.currentTime;
  
  return;
}

void Asset::observeMarket()
{
  // Get the latest price from "news feed", and add to our memory
  readPrices();

  // Calculate the current price levels to buy and sell at
  calcPriceLevels();
  
  // Check whether trade is viable, and if so trade
  waitDays--;
  if (currentTime >= numDays)
    executeTrade();
  
  currentTime++;
  return;
}

void Asset::readPrices()
{
  // Read next price from input stream and add to prices vector
  double currentNumber;
  input >> currentNumber;
  prices.push_back(currentNumber);
  currentPrice = currentNumber;
  return;
}

void Asset::calcPriceLevels()
{
  double sumOfPrices = 0;
  
  for (int t = 1; t <= numDays; t++)
    {
      // For the first few parts of time, we can't do a full rolling average
      if ((currentTime - t) < 0)
	break;

      sumOfPrices += prices[currentTime - t];
    }
  avePrice = sumOfPrices/numDays;
  buyPrice = (1 - downPercent/100) * avePrice;
  sellPrice = (1 + upPercent/100) * avePrice;

  return;
}

void Asset::executeTrade()
{
  double oldQuantity = quantity;
  std::cout << "current price is " << currentPrice << " and buy is " << buyPrice << " and sell is " << sellPrice << std::endl;
  // Make a function that says, depending on how big the delta is, how much we trade
  if (currentPrice <= buyPrice)
    quantity++;
  //	quantity = quantity + std::min(2.5,(currentPrice - buyPrice)*(currentPrice - buyPrice)/100);
  if (currentPrice >= sellPrice)
      //      quantity = std::max(quantity - std::max(5.0, (currentPrice - sellPrice)*(currentPrice - sellPrice)/20), 0.0);
      if (quantity > 0)
	quantity--;
    }
  // Std::cout << "Q is " <<  quantity << std::endl;
  double qChange = oldQuantity - quantity; // How much we sold/bought
  double pChange = qChange * currentPrice; // How did we get/spend
  currentProfit += pChange; // Update total current profit
  profits.push_back(pChange); // Update granular profits

  return;
}

double Asset::getProfit()
{
  std::cout << "The current profit at time " << currentTime << " is " << currentProfit << std::endl;
  return currentProfit;
}

void Asset::writeProfit()
{
  std::ofstream output;
  output.open("profits.csv");
  double sum = 0;
  for (std::vector<double>::iterator it = profits.begin(); it != profits.end(); it++)
    {
      sum += *it;
      output << sum << std::endl;
    }

  output.close();
   
  return;
}
