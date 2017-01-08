#include "Test_Ticker.hpp"

namespace Test
{
	Test_Ticker::Test_Ticker() :
	two(2),
	three(3)
	{

	}

	void Test_Ticker::runTest(Test::Runner &tr)
	{
		tr.newSet("Ticker trigger test");

		tr.test(!two.triggered(), "Length 2 starts off untriggered");
		tr.test(!three.triggered(), "Length 3 starts off untriggered");

		two.tick();
		three.tick();

		tr.test(!two.triggered(), "2 not triggered after 1 tick");
		tr.test(!three.triggered(), "3 not triggered after 1 tick");

		two.tick();
		three.tick();

		tr.test(two.triggered(), "2 triggered after 2 ticks");
		tr.test(!three.triggered(), "3 not triggered after 2 ticks");

		two.tick();
		three.tick();

		tr.test(two.triggered(), "2 still triggered after 3 ticks");
		tr.test(three.triggered(), "3 triggered after 3 ticks");

		tr.endSet();
	}

}
