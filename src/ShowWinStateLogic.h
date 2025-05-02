#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "StateLogic.h"
#include "MyShape.h"
#include "Combination.h"

enum ShowState
{
	checkWin,
	createLine,
	delaySwitch
};

class ShowWinStateLogic : public StateLogic
{
public:
	ShowWinStateLogic(SloteMachineLogic* machine, ControlSlote& flags);
	~ShowWinStateLogic();
	void update(float diff, Statistic& statistic) override;
	void updateStatistic(Statistic& statistic);
	bool exit() override;
private:
	void resetFlags();
	void collectingCombination();
	bool checkWin();
	void fillPositions();
	void createLine();
	void delaySwitch(float diff);
	void showWin(float diff);

	int m_CurrIndex;

	std::vector<sf::Vector2f> m_WinPositions;

	std::vector<Combination> m_WinCombinations;
	Combination* m_curWinCombination;
	std::vector<std::vector<MyShape*>> m_SymbolsOnDisplay;

	ShowState m_State;
	bool m_NeedSwitch;
};