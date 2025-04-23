#pragma once
#include <vector>

#include "State.h"
#include "SloteMachine.h"

class WaitingState : public State
{
public:
	WaitingState(SloteMachine* machine);
	void update(float diff) override;
	bool exit() override;
private:
	SloteMachine* m_Machine;
};