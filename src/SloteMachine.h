#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Slote.h"
#include "MyShape.h"


class SloteMachine
{
public:
	SloteMachine();
	~SloteMachine();
	size_t getCountSlots();
	void draw(sf::RenderTarget& target);
private:
	void fillSymbols();
	void fillSlotes();
	void shuffleSymbols(std::vector<MyShape*>& symbols);
	std::vector<MyShape*> m_Symbols;

	static const size_t countSlots = 3;
	std::vector<Slote> m_Slots;
};