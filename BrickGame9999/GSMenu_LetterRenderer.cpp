#include "GSMenu_LetterRenderer.hpp"
#include "Device.hpp"
#include <cmath>
#include "Global.hpp"

namespace GSMenu
{
	double coef45deg = 0.70710678;

	void LetterRenderer::renderHorizontallyRotatedLetter(Device &dev, std::string letter, int letterW, int letterH, int locationX, int locationY, int steps)
	{
		int degrees = steps * 45;
		double *transform = new double[letterW];

		for (int i = 0; i < letterW; i++)
		{
			transform[i] = i;
		}

		globalToRelative(transform, letterW);

		bool didFlip = false;
		didFlip = applyRotation(transform, letterW, degrees);

		relativeToGlobal(transform, letterW, didFlip);

		for (int x = 0; x < letterW; x++)
		{
			for (int y = 0; y < letterH; y++)
			{
				if (letter[y * letterW + x] == '*')
				{
					dev.screen.mainArray.setPixel(locationX + lround(rint(transform[x])), locationY + y, true);
				}
			}
		}

		delete[] transform;
	}

	void LetterRenderer::globalToRelative(double *transform, int len)
	{
		double div = floor(float(len) / 2);

		if (len % 2 == 0)
		{
			for (int i = 0; i < len; i++)
			{
				transform[i] = transform[i] - div + (i < div ? +1 : 0);
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				transform[i] = transform[i] - div;
			}
		}
	}

	void LetterRenderer::relativeToGlobal(double *transform, int len, bool flipped)
	{
		double div = floor(float(len) / 2);

		if (len % 2 == 0)
		{
			int leftCorrection = flipped ? 0 : -1;
			int rightCorrection = flipped ? -1 : 0;
			for (int i = 0; i < len; i++)
			{
				transform[i] = transform[i] + div + (i < div ? leftCorrection : rightCorrection);
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				transform[i] = transform[i] + div;
			}
		}
	}

	bool LetterRenderer::applyRotation(double *transform, int width, int degrees)
	{
		double multiplier = 0;
		int actualDegrees = 0;
		bool didFlip = false;

		if (degrees > 90 && degrees <= 180)
		{
			actualDegrees = 90 - (180 - degrees);
		}
		else if (degrees > 180 && degrees <= 270)
		{
			actualDegrees = 90 - (degrees - 180);
		}
		else if (degrees > 270 && degrees <= 360)
		{
			actualDegrees = 90 - (360 - degrees);
		}
		else
		{
			actualDegrees = 90 - degrees;
		}

		multiplier = sin(actualDegrees / 180.0 * M_PI);

		for (int i = 0; i < width; i++)
		{
			transform[i] = transform[i] * multiplier;
		}

		if (degrees > 90 && degrees <= 270)
		{
			didFlip = true;
			flip(transform, width);
		}

		return didFlip;
	}

	void LetterRenderer::flip(double *transform, int width)
	{
		int i = 0;
		double temp;
		while (i < width / 2)
		{
			temp = transform[i];
			transform[i] = transform[width - 1 - i];
			transform[width - 1 - i] = temp;
			i++;
		}
	}
}
