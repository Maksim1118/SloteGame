#include "SloteMachineLogic.h"

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
#include "WaitingStateLogic.h"

using namespace sf;
using namespace std;

SloteMachineLogic::SloteMachineLogic()
{
	fillSymbols();
	fillSlotes();
	fillAllCombinations();
	fillWinCombinations();
	m_Selector = new WaitingStateLogic(this, m_FlagsControl);
	m_Statistic.setBalance(balance);
	m_Statistic.setBet(bet);
}

SloteMachineLogic::~SloteMachineLogic()
{
	for (const auto& symbol : m_Symbols)
	{
		delete symbol;
	}
	for (const auto& slote : m_Slots)
	{
		delete slote;
	}
	delete m_Selector;
}

size_t SloteMachineLogic::getCountSlots()
{
	return countSlots;
}


void SloteMachineLogic::setState(StateLogic* newState)
{
	delete m_Selector;
	m_Selector = newState;
}

vector<SloteLogic*>& SloteMachineLogic::getSlots()
{
	return m_Slots;
}

int SloteMachineLogic::getCountSymbols()
{
	return m_Symbols.size();
}

void SloteMachineLogic::run(float diff)
{
	m_Selector->update(diff, m_Statistic);
}

bool SloteMachineLogic::isRunning()
{
	return false;
}

void SloteMachineLogic::start()
{
	m_FlagsControl.startSlote = true;
}

void SloteMachineLogic::stop()
{
	m_FlagsControl.stopSlote = true;
}

vector<shared_ptr<Drawable>> SloteMachineLogic::getObjects() const
{
	return m_Objects;
}

void SloteMachineLogic::addDrawableObject(shared_ptr<Drawable> obj)
{
	m_Objects.emplace_back(obj);
}

void SloteMachineLogic::clearDrawableObjects()
{
	m_Objects.clear();
}

void SloteMachineLogic::fillSymbols()
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

void SloteMachineLogic::fillSlotes()
{
	for (int i = 0; i < countSlots; ++i)
	{
		vector<MyShape*> symbols;
		for (const auto& symbol : m_Symbols)
		{
			symbols.emplace_back(symbol->clone());
		}
		shuffle(symbols);
		SloteLogic* newSlote = new SloteLogic(symbols);
		newSlote->setAccelerate(generateAccelerate());
		m_Slots.emplace_back(newSlote);
	}
}

void SloteMachineLogic::fillWinCombinations()
{
	shuffle(m_AllCombinations);
	for (int i = 0; i < countWinCombinations; ++i)
	{
		m_WinCombinations.emplace_back(m_AllCombinations[i]);
	}
}

void SloteMachineLogic::fillAllCombinations()
{
	int totalUniqueCombinations = pow(m_Symbols.size(), countSlots);
	if (countWinCombinations > totalUniqueCombinations)
	{
		throw invalid_argument("countWinCombinations exceeds the number of possible unique combinations.");
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

float SloteMachineLogic::generateAccelerate()
{
	return generateRandomValue(8.f, 20.f);
}

vector<Combination> SloteMachineLogic::getWinCombinations() const
{
	return m_WinCombinations;
}

Statistic SloteMachineLogic::getStatistic() const
{
	return m_Statistic;
}

template <typename T>
void SloteMachineLogic::shuffle(vector<T>& vec)
{
	for (int i = vec.size() - 1; i > 0; --i)
	{
		int j = generateRandomValue(0, i);
		swap(vec[i], vec[j]);
	}
}

