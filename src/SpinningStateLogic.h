#pragma once
#include "StateLogic.h"

class SpinningStateLogic : public StateLogic
{
public:
	SpinningStateLogic(SloteMachineLogic* machine, ControlSlote& flags);
	void update(float diff, Statistic& statistic) override;
	bool exit() override;
private:
	void spin(float diff);
	void start();
	void deceletateSpin();
	bool m_NeedStop;
};