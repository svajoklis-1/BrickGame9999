#pragma once
#include <string>

class Device;

namespace GSMenu
{
	class LetterRenderer
	{
	public:
		static void LetterRenderer::renderHorizontallyRotatedLetter(Device &dev, std::string letter, int letterW, int letterH, int x, int y, int steps);

	private:
		static void globalToRelative(double *transform, int len);
		static void relativeToGlobal(double *transform, int len, bool flipped);

		static bool applyRotation(double *transform, int width, int degrees);
		static void flip(double *transform, int width);
	};
}
