#pragma once

#include "Test.hpp"

namespace Test
{
	class Runner;

	class Test_LetterRenderer : public AbstractTest
	{
	public:
		Test_LetterRenderer();
		void runTest(Test::Runner &tr) override;

	private:
	};
}
