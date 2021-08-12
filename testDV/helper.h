#pragma once

#include <algorithm>
#include "DvfSimulator.h"


class helper
{

    std::vector <std::pair<double, double>>bids;
    std::vector <std::pair<double, double>>asks;
    #define TOPBIDS 5
    #define NUMBER_OF_BIDS 5

public:
    
    IDvfSimulator* sim;
    DvfSimulator::OrderBook ob;

    helper()
    {

        sim = DvfSimulator::Create();
        bids.clear();
        asks.clear();

    }


    void placeMyOrders(double *myUSD, double *myETH)
    {

        size_t sizeBids = bids.size();
        size_t top5Bids = sizeBids * TOPBIDS / 100;//this marks the 5% of the top

        for (int i = 0; i < NUMBER_OF_BIDS; i++)
        {
            int index = top5Bids > 0 ? rand() % top5Bids : 0;

            double ammountAvailableForThisPrice = bids[index].second;
            double totalValueForThisPrice = bids[index].second * bids[index].first;//in USD

            double maximumToBidFor = totalValueForThisPrice < (*myUSD / 10) ? totalValueForThisPrice : (*myUSD / 10);//in USD
            //divided into 10 to bid for a maximum of 10% of our money!
            double ammountIAmBiddingFor = rand() % (int)maximumToBidFor;

            if (sim->PlaceOrder(bids[index].first, ammountIAmBiddingFor) != std::nullopt)
            {
                *myUSD -= ammountIAmBiddingFor;
                *myETH += ammountIAmBiddingFor / (bids[index].first / bids[index].second);//divide the ammount we spent (in USD) into the value of a unit
            }
        }
        /////////////////

        size_t sizeAsks = asks.size();
        size_t top5Asks = sizeAsks * TOPBIDS / 100;//this marks the 5% of the top

        for (int i = 0; i < NUMBER_OF_BIDS; i++)
        {
            int index = top5Asks > 0 ? rand() % top5Asks : 0;

            double ammountAvailableForThisPrice = asks[index].second;
            double totalValueForThisPrice = asks[index].second * asks[index].first;//in USD

            double maximumToBidFor = totalValueForThisPrice < (*myUSD / 10) ? totalValueForThisPrice : (*myUSD / 10);//in USD
            //divided into 10 to bid for a maximum of 10% of our money!
            double ammountIAmBiddingFor = rand() % (int)maximumToBidFor;

            if (sim->PlaceOrder(asks[index].first, ammountIAmBiddingFor) != std::nullopt)
            {
                *myUSD += ammountIAmBiddingFor;
                *myETH -= ammountIAmBiddingFor / (asks[index].first / asks[index].second);//divide the ammount we spent (in USD) into the value of a unit
            }

        }

    }


    void updateMyListOfBidAndAsk()
    {
        
        bids.clear();
        asks.clear();

        for (int i = 0; i < ob.size(); i++)
        {
            if (ob[i].second > 0)
                bids.push_back(std::make_pair(ob[i].first, ob[i].second));
            else
                asks.push_back(std::make_pair(ob[i].first, abs(ob[i].second)));
        }

        //order theses list
        std::sort(bids.begin(), bids.end(), [](const std::pair<double, double>& a, const std::pair<double, double>& b) { return (a.first / a.second) < (b.first / b.second); });
        std::sort(asks.begin(), asks.end(), [](const std::pair<double, double>& a, const std::pair<double, double>& b) { return (a.first / a.second) < (b.first / b.second); });
        
    }

};