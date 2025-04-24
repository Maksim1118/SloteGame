#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include "Slote.h"
#include "MyShape.h"
#include "State.h"

using Combinations = std::set<std::vector<MyShape*>>;

class SloteMachine
{
public:
	SloteMachine();
	~SloteMachine();
	size_t getCountSlots();
	void draw(sf::RenderTarget& target);
	
	/*void sloteSpin(float diff);*/
	void setState(State* newState);
	std::vector<Slote*>& getSlots();
	void run(float diff);
	bool isRunning();
	void start();
	void stop();
private:
	void fillSymbols();
	void fillSlotes();
	void fillWinCombinations();
	float generateAccelerate();
	bool isUniqueCombination(std::vector<MyShape*> generatedCombination);
	std::vector<MyShape*> & generateWinCombination();
	void shuffleSymbols(std::vector<MyShape*>& symbols);
	std::vector<MyShape*> m_Symbols;

	Combinations m_WinCombinations;

	State* m_Selector;
	bool m_isRunning;
	static const size_t countSlots = 3;
	static const size_t countWinCombination = 5;
	std::vector<Slote*> m_Slots;
};