#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Slote.h"
#include "MyShape.h"
#include "State.h"
#include "Combination.h"
#include "Statistic.h"

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
	std::vector<Combination> getWinCombinations() const;
	Statistic getStatistic() const;
	int getCountSymbols();
	void run(float diff);
	bool isRunning();
	void start();
	void stop();
private:
	void fillSymbols();
	void fillSlotes();
	void fillWinCombinations();
	void fillAllCombinations();
	float generateAccelerate();

	template<typename T>
	void shuffle(std::vector<T>& vec);
	std::vector<MyShape*> m_Symbols;

	std::vector<Combination> m_WinCombinations;
	std::vector<Combination> m_AllCombinations;

	SloteControlFlags m_Flags;
	State* m_Selector;

	Statistic m_Statistic;

	static const size_t countSlots = 3;
	static const int balance = 800;
	const int bet = 20;
	static const size_t countWinCombinations = 60;
	std::vector<Slote*> m_Slots;
};