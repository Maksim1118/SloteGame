#include "SpinningState.h"

#include "WaitingState.h"

using namespace std;

SpinningState::SpinningState(SloteMachine* machine)
	:m_Machine(machine), m_NeedStop(false)
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
	if (!m_Machine->isRunning())
	{
		if (!m_NeedStop)
		{
			stop();
			m_NeedStop = true;
		}
	}

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

void SpinningState::stop()
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->stopSpin();
	}
}
