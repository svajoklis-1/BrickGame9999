#pragma once

namespace GSDefend
{
	class Ship
	{
	public:
		Ship();

		void move(int cells);

	private:
		int x;
		int w;
	};
}