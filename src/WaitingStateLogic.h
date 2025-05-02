#pragma once
#include "StateLogic.h"

class WaitingStateLogic : public StateLogic
{
public:
	WaitingStateLogic(SloteMachineLogic* machine, ControlSlote& flags);
	void update(float diff, Statistic& statistic) override;
	void updateStatistic(Statistic& statistic);
	bool exit() override;
};