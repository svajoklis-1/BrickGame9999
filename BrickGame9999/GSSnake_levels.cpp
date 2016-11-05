#include "GSSnake.h"

namespace GSSnake
{
	void State::defineLevels()
	{
		levelCount = -1;

		levelCount++; // 0
		levels[levelCount] =
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          ";

		levelCount++; // 1
		levels[levelCount] =
			"          "
			"          "
			"  ******  "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"  ******  "
			"          "
			"          ";

		levelCount++; // 2
		levels[levelCount] =
			"          "
			"          "
			"          "
			"          "
			"          "
			"  ******  "
			"  *    *  "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"  *    *  "
			"  ******  "
			"          "
			"          "
			"          "
			"          "
			"          ";

		levelCount++; // 3
		levels[levelCount] =
			"          "
			" ***  *** "
			" *      * "
			" *      * "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			" *      * "
			" *      * "
			" ***  *** "
			"          ";

		levelCount++; // 4
		levels[levelCount] =
			"***    ***"
			"*        *"
			"*        *"
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"*        *"
			"*        *"
			"***    ***";

		levelCount++; // 5
		levels[levelCount] =
			"***    ***"
			"*        *"
			"*        *"
			"          "
			"          "
			"          "
			"   ****   "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"   ****   "
			"          "
			"          "
			"          "
			"*        *"
			"*        *"
			"***    ***";

		levelCount++; // 6
		levels[levelCount] =
			"***    ***"
			"*        *"
			"*        *"
			"          "
			"  ******  "
			"  *    *  "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"          "
			"  *    *  "
			"  ******  "
			"          "
			"          "
			"*        *"
			"*        *"
			"***    ***";

		levelCount++; // 7
		levels[levelCount] =
			"***    ***"
			"*        *"
			"*        *"
			"          "
			"  ******  "
			"  *    *  "
			"          "
			"  ******  "
			"          "
			"          "
			"          "
			"  ******  "
			"          "
			"  *    *  "
			"  ******  "
			"          "
			"          "
			"*        *"
			"*        *"
			"***    ***";
	}
}
