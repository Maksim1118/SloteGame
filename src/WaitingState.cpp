#include "WaitingState.h"
#include "SpinningState.h"
#include "SloteMachine.h"


using namespace std;
using namespace sf;

WaitingState::WaitingState(SloteMachine* machine, SloteControlFlags& flags) : State(machine, flags)
{

}

void WaitingState::update(float diff, Statistic& statistic)
{
	if (statistic.getWin() != 0)
		statistic.addWin(-statistic.getWin());
	if (exit())
	{
		updateStatistic(statistic);
		m_Machine->setState(new SpinningState(m_Machine, m_Flags));
	}
}

void WaitingState::updateStatistic(Statistic& statistic)
{
	statistic.setBalance(statistic.getBalance() - statistic.getBet());
}

bool WaitingState::exit()
{
	if (!m_Flags.isRunning && m_Flags.startSlote)
	{
		m_Flags.isRunning = true;
		return true;
	}
	return false;
}

void WaitingState::draw(RenderTarget& target) const
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->draw(target);
	}
}
