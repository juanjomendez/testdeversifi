#include "pch.h"
#include "CppUnitTest.h"
#include "../testDV/helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testForTestDV
{
	TEST_CLASS(testForTestDV)
	{
		IDvfSimulator* sim;
		helper* hpl;
		
	public:
		
		TEST_METHOD(Creation)
		{
			sim = DvfSimulator::Create();
		}

		TEST_METHOD(getOrderBook)
		{
			sim = DvfSimulator::Create();
			sim->GetOrderBook();
		}

		TEST_METHOD(updateLists)
		{
			sim = DvfSimulator::Create();
			sim->GetOrderBook();
			hpl = new helper();

			std::vector <std::pair<double, double>>bids;
			std::vector <std::pair<double, double>>asks;

			hpl->updateMyListOfBidAndAsk();
		}
		
	};
}
