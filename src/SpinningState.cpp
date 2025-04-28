#include "SpinningState.h"

#include "ShowWinState.h"
#include "SloteMachine.h"

using namespace std;

SpinningState::SpinningState(SloteMachine* machine, SloteControlFlags& flags)
	:State(machine, flags), m_NeedStop(false)
{
	start();
}

void SpinningState::update(float diff, Statistic& statistic)
{
	spin(diff);
	if (exit())
	{
		m_Machine->setState(new ShowWinState(m_Machine, m_Flags));
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

void SpinningState::draw(sf::RenderTarget& target) const
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->draw(target);
	}
}

void SpinningState::spin(float diff)
{
	if (m_Flags.isRunning && m_Flags.stopSlote)
	{
		if (!m_NeedStop)
		{
			deceletateSpin();
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

void SpinningState::deceletateSpin()
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->stopSpin();
	}
}
