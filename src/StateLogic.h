#pragma once
#include "Statistic.h"
#include "ControlSlote.h"

class SloteMachineLogic;

class StateLogic
{
public:
	StateLogic(SloteMachineLogic* machine, ControlSlote& flags);
	virtual ~StateLogic() = default;
	virtual void update(float diff, Statistic& statistic) = 0;
	virtual bool exit() = 0;
protected:
	SloteMachineLogic* m_MachineLogic;
	ControlSlote& m_FlagsControl;
};