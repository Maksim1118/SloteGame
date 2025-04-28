#include "ShowWinState.h"

#include <iostream>

#include "WaitingState.h"
#include "SloteMachine.h"

using namespace std;
using namespace sf;

float delay = 1.f;

ShowWinState::ShowWinState(SloteMachine* machine, SloteControlFlags& flags)
	:State(machine, flags), m_CurrIndex(0), m_NeedSwitch(false), m_curWinCombination(nullptr)
{
	m_State = ShowState::checkWin;
	collectingCombination();
	m_WinCombinations = m_Machine->getWinCombinations();
}

void ShowWinState::update(float diff, Statistic& statistic)
{
	showWin(diff);
	updateStatistic(statistic);
	if (exit())
	{ 
		resetFlags();
		m_Lines.shrink_to_fit();
		m_Machine->setState(new WaitingState(m_Machine, m_Flags));
	}
}

void ShowWinState::updateStatistic(Statistic& statistic)
{
	if (m_curWinCombination == nullptr)
		return;
	int winAmount = m_curWinCombination->getWinAmount();
	statistic.addWin(winAmount);
	statistic.setBalance(statistic.getBalance() + statistic.getWin());
	m_curWinCombination = nullptr;
}

bool ShowWinState::exit()
{
	if (m_NeedSwitch)
	{
		m_NeedSwitch = false;
		return true;
	}
	return false;
}

void ShowWinState::draw(RenderTarget& target) const
{
	for (const auto& slote : m_Machine->getSlots())
	{
		slote->draw(target);
	}

	for (const auto& line : m_Lines)
	{
		target.draw(line);
	}
	
}

void ShowWinState::resetFlags()
{
	m_Flags = { false, false ,false };
}

void ShowWinState::collectingCombination()
{
	int countSymbols = m_Machine->getCountSymbols();

	for (int i = 0; i < countSymbols; ++i)
	{
		vector<MyShape*> symbols;
		for (const auto& slote: m_Machine->getSlots())
		{ 
			symbols.emplace_back(slote->getSymbol(i));
		}
		m_SymbolsOnDisplay.emplace_back(symbols);
	}
}

bool ShowWinState::checkWin()
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

void ShowWinState::fillPositions()
{
	for (int j = 0; j < m_Machine->getCountSlots(); ++j)
	{
		m_WinPositions.emplace_back(m_SymbolsOnDisplay[m_CurrIndex][j]->getCenter());
	}
	if (m_WinPositions.empty())
	{
		cerr << "positions empty" << endl;
	}
}

void ShowWinState::createLine()
{
	vector<Vector2f> points = m_WinPositions;
	m_WinPositions.clear();
	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		Vector2f start = points[i];
		Vector2f end = points[i + 1];
		Vector2f direction = end - start;

		float length = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction /= length;

		RectangleShape line(Vector2f(length, 10.f));
		line.setOrigin(0, 5.f);
		line.setPosition(start);
		line.setFillColor(Color(120, 120, 120));
		line.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159);

		m_Lines.push_back(line);
	}
}

void ShowWinState::delaySwitch(float diff)
{
	delay -= diff;
}

void ShowWinState::showWin(float diff)
{
	if (m_CurrIndex > m_Machine->getCountSymbols() - 1)
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
				m_State = ShowState::drawLine;
			}
			else
			{
				m_CurrIndex++;
			}
			break;
		}
		case ShowState::drawLine:
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
				m_Lines.clear();
			}
			break;
		}

	}
}
