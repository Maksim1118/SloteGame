#include "SpinningState.h"

#include "WaitingState.h"

using namespace std;

SpinningState::SpinningState(SloteMachine* machine)
	:m_Machine(machine)
{
	start();
}

void SpinningState::update(float diff)
{
	spin(diff);
	if (exit())
	{
		m_Machine->stop();
		m_Machine->setState(new WaitingState(m_Machine));
	}
}

bool SpinningState::exit()
{
	for (const auto& slote : m_Machine->getSlots())
	{
		if (!slote->isSpinStoped())
			return false;
	}
	return true;
}

void SpinningState::spin(float diff)
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->spin(diff);
	}
}

void SpinningState::start()
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->startSpin();
	}
}
