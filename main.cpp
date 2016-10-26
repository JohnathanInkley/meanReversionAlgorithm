// Filename: main.cpp
// Author: Johnathan Inkley
// Date: 2016 10 26
// Description: A program that takes asset prices (faux real time), and trades them

#include <iostream>
#include <fstream>
#include <vector>
#include "Asset.h"

int main()
{
  std::ifstream assetPrices;
  assetPrices.open("GOOGL1.csv");
  Asset anAsset(2,2,5, assetPrices);  

  for (int t = 0; t <= 3068; t++)
    {
      anAsset.observeMarket();
      anAsset.getProfit();
    }
  anAsset.writeProfit();
  assetPrices.close();
  return 0;
}
