#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SloteLogic.h"
#include "StateLogic.h"
#include "MyShape.h"
#include "Combination.h"
#include "Statistic.h"
#include "ControlSlote.h"

class SloteMachineLogic
{
public:
	SloteMachineLogic();
	~SloteMachineLogic();
	size_t getCountSlots();
	void setState(StateLogic* newState);
	std::vector<SloteLogic*>& getSlots();
	std::vector<Combination> getWinCombinations() const;
	Statistic getStatistic() const;
	int getCountSymbols();
	void run(float diff);
	bool isRunning();
	void start();
	void stop();
	std::vector<std::shared_ptr<sf::Drawable>> getObjects() const;
	void addDrawableObject(std::shared_ptr<sf::Drawable> obj);
	void clearDrawableObjects();
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

	ControlSlote m_FlagsControl;
	StateLogic* m_Selector;

	Statistic m_Statistic;

	static const size_t countSlots = 3;
	static const int balance = 800;
	static const int bet = 20;
	static const size_t countWinCombinations = 60;
	std::vector<SloteLogic*> m_Slots;
	std::vector<std::shared_ptr<sf::Drawable>> m_Objects;
};