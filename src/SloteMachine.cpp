#include "SloteMachine.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Generator.h"
#include "Colors.h"
#include "Variables.h"
#include "Star.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "WaitingState.h"

using namespace sf;
using namespace std;

SloteMachine::SloteMachine()
	:m_Flags{false, false, false}
{
	fillSymbols();
	fillSlotes();
	fillAllCombinations();
	fillWinCombinations();
	m_Selector = new WaitingState(this, m_Flags);
	m_Statistic.setBalance(balance);
	m_Statistic.setBet(bet);
}

SloteMachine::~SloteMachine()
{
	for (const auto& symbol : m_Symbols)
	{
		delete symbol;
	}
	for (const auto& slote : m_Slots)
	{
		delete slote;
	}
}

size_t SloteMachine::getCountSlots()
{
	return countSlots;
}

void SloteMachine::draw(RenderTarget& target)
{
	/*for (const auto& slote : m_Slots)
	{
		slote->draw(target);
	}*/
	m_Selector->draw(target);
}

void SloteMachine::setState(State* newState)
{
	m_Selector = newState;
}

vector<Slote*>& SloteMachine::getSlots()
{
	return m_Slots;
}

int SloteMachine::getCountSymbols()
{
	return m_Symbols.size();
}

void SloteMachine::run(float diff)
{
	m_Selector->update(diff, m_Statistic);
}

bool SloteMachine::isRunning()
{
	return false;
}

void SloteMachine::start()
{
	m_Flags.startSlote = true;
}

void SloteMachine::stop()
{
	m_Flags.stopSlote = true;
}

void SloteMachine::fillSymbols()
{
	Star* star = new Star();
	star->setSize(symbolSize / 2.f, symbolSize);
	m_Symbols.emplace_back(star);

	Triangle* triangle = new Triangle();
	triangle->setSize(symbolSize);
	m_Symbols.emplace_back(triangle);

	Rectangle* rectangle = new Rectangle();
	rectangle->setSize({ symbolSize, symbolSize });
	m_Symbols.emplace_back(rectangle);

	Circle* circle = new Circle();
	circle->setRadius(symbolSize / 2.f);
	m_Symbols.emplace_back(circle);

	Colors colors = getSymbolColors();
	if (colors.size() < m_Symbols.size())
	{
		throw runtime_error("the size of the color array for symbols is less than the size of the symbol array");
	}
	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		m_Symbols[i]->setFillColor(colors[i]);
	}
}

void SloteMachine::fillSlotes()
{
	for (int i = 0; i < countSlots; ++i)
	{
		vector<MyShape*> symbols;
		for (const auto& symbol : m_Symbols)
		{
			symbols.emplace_back(symbol->clone());
		}
		shuffle(symbols);
		Slote* newSlote = new Slote(symbols);
		newSlote->setAccelerate(generateAccelerate());
		m_Slots.emplace_back(newSlote);
	}
}

void SloteMachine::fillWinCombinations()
{
	shuffle(m_AllCombinations);
	for (int i = 0; i < countWinCombinations; ++i)
	{
		m_WinCombinations.emplace_back(m_AllCombinations[i]);
	}
}

void SloteMachine::fillAllCombinations()
{
	int totalUniqueCombinations = pow(m_Symbols.size(), countSlots);
	if (countWinCombinations > totalUniqueCombinations)
	{
		throw std::invalid_argument("countWinCombinations exceeds the number of possible unique combinations.");
	}
	int countSymbols = m_Symbols.size();
	for (int i = 0; i < totalUniqueCombinations; ++i)
	{
		vector<int> symbols;
		int temp = i;
		for (int j = 0; j < countSlots; ++j)
		{
			int index = temp % countSymbols;
			symbols.emplace_back(m_Symbols[index]->getID());
			temp /= countSymbols;
		}
		m_AllCombinations.emplace_back(symbols, generateRandomValue(20, 100));
	}
}

float SloteMachine::generateAccelerate()
{
	return generateRandomValue(2.f, 5.f);
}

vector<Combination> SloteMachine::getWinCombinations() const
{
	return m_WinCombinations;
}

Statistic SloteMachine::getStatistic() const
{
	return m_Statistic;
}


//void SloteMachine::sloteSpin(float diff)
//{
//	for (auto& slote : m_Slots)
//	{
//		slote->spin(diff);
//	}
//}

template <typename T>
void SloteMachine::shuffle(vector<T>& vec)
{
	for (int i = vec.size() - 1; i > 0; --i)
	{
		int j = generateRandomValue(0, i);
		swap(vec[i], vec[j]);
	}
}

