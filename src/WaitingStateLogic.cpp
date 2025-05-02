#include "WaitingStateLogic.h"
#include "SpinningStateLogic.h"
#include "SloteMachineLogic.h"


using namespace std;

WaitingStateLogic::WaitingStateLogic(SloteMachineLogic* machine, ControlSlote& flags) : StateLogic(machine, flags)
{

}

void WaitingStateLogic::update(float diff, Statistic& statistic)
{
	if (statistic.getWin() != 0)
		statistic.addWin(-statistic.getWin());
	if (exit())
	{
		updateStatistic(statistic);
		if(m_FlagsControl.stopSlote)
			m_FlagsControl.stopSlote = false;
		m_MachineLogic->setState(new SpinningStateLogic(m_MachineLogic, m_FlagsControl));
	}
}

void WaitingStateLogic::updateStatistic(Statistic& statistic)
{
	statistic.setBalance(statistic.getBalance() - statistic.getBet());
}

bool WaitingStateLogic::exit()
{
	if (!m_FlagsControl.isRunning && m_FlagsControl.startSlote)
	{
		m_FlagsControl.isRunning = true;
		return true;
	}
	return false;
}
