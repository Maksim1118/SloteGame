#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SloteDraw.h"
#include "Statistic.h"

class SloteMachineLogic;

class SloteMachineDraw
{
public:
	SloteMachineDraw(SloteMachineLogic* machineLogic);
	~SloteMachineDraw();
	void draw(sf::RenderTarget& target);
	std::vector<SloteDraw*>& getSlots();
	int getCountSlots();
	Statistic getStatistic() const;
private:
	void fillSloteDraws();
	SloteMachineLogic* m_MachineLogic;
	std::vector<SloteDraw*> m_SloteDraws;
};