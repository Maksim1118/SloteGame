#pragma once
#include <vector>
#include <memory>

#include "SloteMachineLogic.h"
#include "TextButton.h"
#include "Statistic.h"

class GameScene
{
public:
	GameScene();
	~GameScene();
	void timeElapsed(float diff, sf::Vector2f mousePos);
	void hangleEvent(sf::Event& event, sf::Vector2f mousePos);
	SloteMachineLogic* getMachine();
	std::vector<Button*>& getButtons();
private:
	void initButtons();
	void updateButtons(sf::Vector2f mousePos);
	std::unique_ptr<SloteMachineLogic> m_MachineLogic;
	TextButton* m_StartButton;
	TextButton* m_StopButton;
	std::vector<Button*> m_Buttons;
};