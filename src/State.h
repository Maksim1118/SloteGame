#pragma once
#include <SFML/Graphics.hpp>
#include "Statistic.h"
class SloteMachine;

struct SloteControlFlags
{
	bool isRunning;
	bool startSlote;
	bool stopSlote;
};

class State
{
public:
	State(SloteMachine* machine, SloteControlFlags& flags);
	virtual ~State() = default;
	virtual void update(float diff, Statistic& statistic) = 0;
	virtual bool exit() = 0;
	virtual void draw(sf::RenderTarget& target) const = 0;
protected:
	SloteMachine* m_Machine;
	SloteControlFlags& m_Flags;
	bool m_isUpdateStatistic;
};