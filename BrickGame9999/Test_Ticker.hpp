#pragma once

#include "Test.hpp"
#include "Test_Runner.hpp"
#include "Ticker.hpp"

namespace Test
{
	class Test_Ticker : public AbstractTest
	{
	public:
		Test_Ticker();
		void runTest(Test::Runner &tr) override;

	private:
		Ticker two;
		Ticker three;
	};
}
