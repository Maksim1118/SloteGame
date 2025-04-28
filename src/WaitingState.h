#pragma once
#include <vector>

#include "State.h"

class WaitingState : public State
{
public:
	WaitingState(SloteMachine* machine, SloteControlFlags& flags);
	void update(float diff, Statistic& statistic) override;
	void updateStatistic(Statistic& statistic);
	bool exit() override;
	void draw(sf::RenderTarget& target)const override;
};