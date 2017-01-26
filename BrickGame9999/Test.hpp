#pragma once

#include "Test_Runner.hpp"

namespace Test
{
	class AbstractTest
	{
	public:
		virtual void runTest(Test::Runner &tr) = 0;
		virtual ~AbstractTest() { };
	};
}
