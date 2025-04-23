#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Slote.h"
#include "MyShape.h"
#include "State.h"

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
private:
	void fillSymbols();
	void fillSlotes();
	float generateAccelerate();
	void shuffleSymbols(std::vector<MyShape*>& symbols);
	std::vector<MyShape*> m_Symbols;

	State* m_Selector;
	static const size_t countSlots = 3;
	std::vector<Slote*> m_Slots;
};