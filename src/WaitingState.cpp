#include "WaitingState.h"
#include "SpinningState.h"

using namespace std;

WaitingState::WaitingState(SloteMachine* machine)
	:m_Machine(machine)
{

}

void WaitingState::update(float diff)
{
	if (exit())
	{
		m_Machine->setState(new SpinningState(m_Machine));
	}
}

bool WaitingState::exit()
{
	return m_Machine->isRunning();
}
