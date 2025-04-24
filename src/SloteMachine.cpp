#include "SloteMachine.h"

#include <stdexcept>

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
	:m_isRunning(false)
{
	fillSymbols();
	fillSlotes();
	m_Selector = new WaitingState(this);
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

void SloteMachine::draw(sf::RenderTarget& target)
{
	for (const auto& slote : m_Slots)
	{
		slote->draw(target);
	}
}

void SloteMachine::setState(State* newState)
{
	m_Selector = newState;
}

std::vector<Slote*>& SloteMachine::getSlots()
{
	return m_Slots;
}

void SloteMachine::run(float diff)
{
	m_Selector->update(diff);
}

bool SloteMachine::isRunning()
{
	return m_isRunning;
}

void SloteMachine::start()
{
	m_isRunning = true;
}

void SloteMachine::stop()
{
	m_isRunning = false;
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
		shuffleSymbols(symbols);
		Slote* newSlote = new Slote(symbols);
		newSlote->setAccelerate(generateAccelerate());
		m_Slots.emplace_back(newSlote);
	}
}

void SloteMachine::fillWinCombinations()
{
	for (int i = 0; i < countWinCombination; ++i)
	{
		vector<MyShape*> combination;
		do
		{
			combination = generateWinCombination();
		} while (!isUniqueCombination(combination));

		m_WinCombinations.emplace_back(combination);
	}
}

float SloteMachine::generateAccelerate()
{
	return generateRandomValue(2.f, 5.f);
}

bool SloteMachine::isUniqueCombination(vector<MyShape*> generatedCombination)
{
	for (const auto& combination : m_WinCombinations)
	{
		for (int i = 0; i < combination.size(); ++i)
		{
			if(combination[i] == generatedCombination[i])
				return false;
		}
	}
	return true;
}

vector<MyShape*>& SloteMachine::generateWinCombination()
{
	int countSymbols = m_Symbols.size();
	vector<MyShape*> winSymbols;
	for (int i = 0; i < countSlots; ++i)
	{
		int index = generateRandomValue(0, countSymbols-1);
		winSymbols.emplace_back(m_Symbols[index]->clone());
	}
	return winSymbols;
}

//void SloteMachine::sloteSpin(float diff)
//{
//	for (auto& slote : m_Slots)
//	{
//		slote->spin(diff);
//	}
//}

void SloteMachine::shuffleSymbols(vector<MyShape*>& symbols)
{
	for (int i = symbols.size() - 1; i > 0; --i)
	{
		int j = generateRandomValue(0, i);
		swap(symbols[i], symbols[j]);
	}
}

