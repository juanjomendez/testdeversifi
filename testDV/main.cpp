
#include <conio.h>
#include <algorithm>
#include "DvfSimulator.h"
#include "helper.h"
#include "main.h"


void mainLoop()
{

    time_t begin1, end1;
    time_t begin2, end2;

    char cKey=' ';

    time(&begin1);
    time(&begin2);

    while (cKey != 'q')
    {

        time(&end1);
        time_t elapsedTime1 = end1 - begin1;
        if (elapsedTime1 >= TIME_NEEDED_FOR_REFRESH)
        {
            myHelper->ob.clear();
            myHelper->ob = myHelper->sim->GetOrderBook();
            myHelper->updateMyListOfBidAndAsk();
            myHelper->placeMyOrders(&myUSD, &myETH);
            time(&begin1);
        }

        time(&end2);
        time_t elapsedTime2 = end2 - begin2;
        if (elapsedTime2 >= TIME_NEEDED_FOR_ASSET_BALANCE)
        {
            std::cout << "BALANCE:  USD = " << myUSD << ", ETH = " << myETH << "\n";
            time(&begin2);
        }

        if (_kbhit())
            cKey = _getch();

    }

}


int main()
{
    std::cout << "Press 'q' to exit\n";
    myHelper = new helper();

    mainLoop();
    
    return true;

}