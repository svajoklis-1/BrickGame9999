#pragma once
#include <string>

namespace Test
{
	class Runner
	{
	public:
		Runner();

		void newSet(std::string name);
		void endSet();
		void run();

		void test(int actual, int expected, std::string description);
		void test(bool condition, std::string description);

	private:
		void resetSet();
		void end();
		void logRunStatus(int successful, int total);
		void logTestStatus(bool success);
		
		bool setStarted;
		std::string setName;

		int testsInSet;
		int successfulTestsInSet;

		int testsTotal;
		int successfulTestsTotal;
	};
}
