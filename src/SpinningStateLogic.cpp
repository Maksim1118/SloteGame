#include "SpinningStateLogic.h"

#include "ShowWinStateLogic.h"
#include "SloteMachineLogic.h"


SpinningStateLogic::SpinningStateLogic(SloteMachineLogic* machine, ControlSlote& flags)
	:StateLogic(machine, flags), m_NeedStop(false)
{
	start();
}

void SpinningStateLogic::update(float diff, Statistic& statistic)
{
	spin(diff);
	if (exit())
	{
		m_MachineLogic->setState(new ShowWinStateLogic(m_MachineLogic, m_FlagsControl));
	}
}

bool SpinningStateLogic::exit()
{
	for (const auto& slote : m_MachineLogic->getSlots())
	{
		if (!slote->isSpinStoped())
			return false;
	}
	return true;
}

void SpinningStateLogic::spin(float diff)
{
	if (m_FlagsControl.isRunning && m_FlagsControl.stopSlote)
	{
		if (!m_NeedStop)
		{
			deceletateSpin();
			m_NeedStop = true;
		}
	}

	for (const auto& slote : m_MachineLogic->getSlots())
	{
		slote->spin(diff);
	}
}

void SpinningStateLogic::start()
{
	for (const auto& slote : m_MachineLogic->getSlots())
	{
		slote->startSpin();
	}
}

void SpinningStateLogic::deceletateSpin()
{
	for (const auto& slote : m_MachineLogic->getSlots())
	{
		slote->stopSpin();
	}
}
