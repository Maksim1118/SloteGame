#pragma once
#include <vector>

#include "State.h"

class SpinningState: public State
{
public:
	SpinningState(SloteMachine* machine, SloteControlFlags& flags);
	void update(float diff, Statistic& statistic) override;
	bool exit() override;
	void draw(sf::RenderTarget& target) const override;
private:
	void spin(float diff);
	void start();
	void deceletateSpin();
	bool m_NeedStop;
};