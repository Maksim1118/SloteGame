#pragma once
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

#include "State.h"
#include "WaitingState.h"
#include "MyShape.h"
#include "Combination.h"

enum ShowState
{
	checkWin,
	drawLine,
	delaySwitch
};

class ShowWinState : public State
{
public:
	ShowWinState(SloteMachine* machine, SloteControlFlags& flags);
	void update(float diff, Statistic& statistic) override;
	void updateStatistic(Statistic& statistic);
	bool exit() override;
	void draw(sf::RenderTarget& target) const override;
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

	std::vector<sf::RectangleShape> m_Lines;
	bool m_NeedSwitch;
};