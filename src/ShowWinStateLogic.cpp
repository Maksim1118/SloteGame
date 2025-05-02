#include "ShowWinStateLogic.h"

#include <iostream>
#include <memory>

#include "WaitingStateLogic.h"
#include "SloteMachineLogic.h"

using namespace std;
using namespace sf;

float delay = 1.f;

ShowWinStateLogic::ShowWinStateLogic(SloteMachineLogic* machine, ControlSlote& flags)
	:StateLogic(machine, flags), m_CurrIndex(0), m_NeedSwitch(false), m_curWinCombination(nullptr)
{
	m_State = ShowState::checkWin;
	collectingCombination();
	m_WinCombinations = m_MachineLogic->getWinCombinations();
}

ShowWinStateLogic::~ShowWinStateLogic()
{
	m_MachineLogic->clearDrawableObjects();
}

void ShowWinStateLogic::update(float diff, Statistic& statistic)
{
	showWin(diff);
	updateStatistic(statistic);
	if (exit())
	{
		resetFlags();
		m_MachineLogic->setState(new WaitingStateLogic(m_MachineLogic, m_FlagsControl));
	}
}

void ShowWinStateLogic::updateStatistic(Statistic& statistic)
{
	if (m_curWinCombination == nullptr)
		return;
	int winAmount = m_curWinCombination->getWinAmount();
	statistic.addWin(winAmount);
	statistic.setBalance(statistic.getBalance() + statistic.getWin());
	m_curWinCombination = nullptr;
}

bool ShowWinStateLogic::exit()
{
	if (m_NeedSwitch)
	{
		m_NeedSwitch = false;
		return true;
	}
	return false;
}

void ShowWinStateLogic::resetFlags()
{
	m_FlagsControl.isRunning = false;
	m_FlagsControl.startSlote = false;
	m_FlagsControl.stopSlote = false;
}

void ShowWinStateLogic::collectingCombination()
{
	int countSymbols = m_MachineLogic->getCountSymbols();

	for (int i = 0; i < countSymbols; ++i)
	{
		vector<MyShape*> symbols;
		for (const auto& slote : m_MachineLogic->getSlots())
		{
			symbols.emplace_back(slote->getSymbol(i));
		}
		m_SymbolsOnDisplay.emplace_back(symbols);
	}
}

bool ShowWinStateLogic::checkWin()
{
	for (int i = 0; i < m_WinCombinations.size(); ++i)
	{
		bool match = true;

		m_curWinCombination = &m_WinCombinations[i];
		vector<int> combination = m_curWinCombination->getCombination();
		for (int j = 0; j < combination.size(); ++j)
		{
			if (combination[j] != m_SymbolsOnDisplay[m_CurrIndex][j]->getID())
			{
				m_curWinCombination = nullptr;
				match = false;
				break;
			}
		}

		if (match)
		{
			m_curWinCombination;
			return true;
		}
	}
	return false;
}

void ShowWinStateLogic::fillPositions()
{
	for (int j = 0; j < m_MachineLogic->getCountSlots(); ++j)
	{
		m_WinPositions.emplace_back(m_SymbolsOnDisplay[m_CurrIndex][j]->getCenter());
	}
	if (m_WinPositions.empty())
	{
		cerr << "positions empty" << endl;
	}
}

void ShowWinStateLogic::createLine()
{
	vector<Vector2f> points = m_WinPositions;
	m_WinPositions.clear();
	m_MachineLogic->clearDrawableObjects();
	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		Vector2f start = points[i];
		Vector2f end = points[i + 1];
		Vector2f direction = end - start;

		float length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;

		auto line  = make_shared<RectangleShape>(Vector2f(length, 10.f));
		line->setOrigin(0, 5.f);
		line->setPosition(start);
		line->setFillColor(Color(120, 120, 120));
		line->setRotation(atan2(direction.y, direction.x) * 180 / 3.14159);

		m_MachineLogic->addDrawableObject(line);
	}
}

void ShowWinStateLogic::delaySwitch(float diff)
{
	delay -= diff;
}

void ShowWinStateLogic::showWin(float diff)
{
	if (m_CurrIndex > m_MachineLogic->getCountSymbols() - 1)
	{ 
		m_NeedSwitch = true;
		return;
	}
	switch (m_State)
	{
		case ShowState::checkWin:
		{
			if (checkWin())
			{
				m_State = ShowState::createLine;
			}
			else
			{
				m_CurrIndex++;
			}
			break;
		}
		case ShowState::createLine:
		{
			fillPositions();
			createLine();
			m_State = ShowState::delaySwitch;
			break;
		}
		case ShowState::delaySwitch:
		{
			delaySwitch(diff);
			if (delay <= 0.f)
			{
				delay = 1.f;
				m_State = ShowState::checkWin;
				m_CurrIndex++;
			}
			break;
		}

	}
}
