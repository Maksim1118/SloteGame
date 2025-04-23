#pragma once
#include <vector>

#include "State.h"
#include "SloteMachine.h"

class SpinningState: public State
{
public:
	SpinningState(SloteMachine* machine);
	void update(float diff) override;
	bool exit() override;
private:
	void spin(float diff);
	SloteMachine* m_Machine;
};