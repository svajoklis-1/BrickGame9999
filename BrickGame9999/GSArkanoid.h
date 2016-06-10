#include "GameState.h"
#include "Ticker.h"
#include "Explosion.h"

enum GSArkanoidVariant
{
	GSARKANOID_NORMAL,
	GSARKANOID_DOUBLE
};

class GSArkanoid : public GameState
{
public:
	GSArkanoid(Device &dev, GSArkanoidVariant variant);
	void tick(Device& dev) override;
	void parseEvent(Device& dev, Key k, KeyState state) override;
	void render(Device& dev) override;
	~GSArkanoid() override;



private:
	GSArkanoidVariant currentVariant;
	
	enum stateSegments
	{
		SEG_PAUSE = 0,
		SEG_GAME,
		SEG_EXPLOSION
	};

	void reset(Device &dev);
	void resetLevel(Device &dev);

	static string currentLevel;
	static int currentCount;

	int stateSegment = 0;
	char highScoreLetter;

	void tickPause(Device &dev);
	void tickGame(Device &dev);
	void tickExplosion(Device &dev);
	void renderGame(Device &dev);

	Ticker ballTicker;
	Ticker paddleTicker;

	int paddleX = 3;
	int paddleW = 4;
	int paddleDX = 0;

	int ballX = 5;
	int ballY = 18;
	int ballDX = 1;
	int ballDY = -1;
	bool slid = false;

	int levelCount = 0;

	Ticker pauseTicker;

	Explosion explosion;

	struct level
	{
		string data;
		int count;
	};
	map<int, level> levels;
	void defineLevels();
};