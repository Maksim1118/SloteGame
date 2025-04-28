#include "State.h"

State::State(SloteMachine* machine, SloteControlFlags& flags)
	:m_Machine(machine), m_Flags(flags), m_isUpdateStatistic(false)
{

}
