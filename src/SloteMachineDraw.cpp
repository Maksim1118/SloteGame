#include "SloteMachineDraw.h"
#include "SloteMachineLogic.h"

using namespace std;
using namespace sf;

SloteMachineDraw::SloteMachineDraw(SloteMachineLogic* machineLogic)
	:m_MachineLogic(machineLogic)
{
	fillSloteDraws();
}

SloteMachineDraw::~SloteMachineDraw()
{
	for (const auto& slote : m_SloteDraws)
	{
		delete slote;
	}
}

void SloteMachineDraw::draw(RenderTarget& target)
{
	for (const auto& slote : m_SloteDraws)
	{
		slote->draw(target);
	}

	for (const auto& obj : m_MachineLogic->getObjects())
	{
		target.draw(*obj);
	}
}

vector<SloteDraw*>& SloteMachineDraw::getSlots()
{
	return m_SloteDraws;
}

int SloteMachineDraw::getCountSlots()
{
	return m_SloteDraws.size();
}

Statistic SloteMachineDraw::getStatistic() const
{
	return m_MachineLogic->getStatistic();
}


void SloteMachineDraw::fillSloteDraws()
{
	for (auto& slote : m_MachineLogic->getSlots())
	{
		SloteDraw* sloteDraw = new SloteDraw(slote);
		m_SloteDraws.emplace_back(sloteDraw);
	}
}

