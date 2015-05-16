#include "GameState.h"

enum GSArkanoidVariant
{
	GSARKANOID_NORMAL,
	GSARKANOID_DOUBLE
};

class GSArkanoid : public GameState
{
public:
	void tick(Device& dev) override;
	void parseEvent(Device& dev, Key k, KeyState state) override;
	void render(Device& dev) override;
	~GSArkanoid() override;
};