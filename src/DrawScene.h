#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Statistic.h"
#include "SloteMachineDraw.h"
#include "ButtonRender.h"

class GameScene;

class DrawScene
{
public:
	DrawScene(GameScene* scene);
	void draw(sf::RenderWindow& window);
private:
	void createFrame();
	void initStatisticText();
	void updateStatistic(Statistic& statistic);
	void fillButtonsRender();
	GameScene* m_Scene;
	sf::Text m_WinText;
	sf::Text m_BalanceText;
	sf::Text m_BetText;
	std::unique_ptr<SloteMachineDraw> m_MachineDraw;
	sf::RenderTexture m_Mask;
	std::vector<sf::RectangleShape> m_SloteFrame;
	std::vector<ButtonRender> m_Buttons;
};