#include "WaitingState.h"

using namespace std;

WaitingState::WaitingState(SloteMachine* machine)
	:m_Machine(machine)
{

}

void WaitingState::update(float diff)
{
	wait();
}

bool WaitingState::exit()
{
	return true;
}

void WaitingState::wait()
{
	/*for (const auto& slote : m_Slots)
	{
		slote->startSpin();
	}*/
}