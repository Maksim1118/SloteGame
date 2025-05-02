#include "DrawScene.h"

#include "GameScene.h"
#include "Variables.h"
#include "Colors.h"
#include "ResourceManager.h"

using namespace std;
using namespace sf;

DrawScene::DrawScene(GameScene* scene)
	:m_Scene(scene)
{
	m_MachineDraw = make_unique<SloteMachineDraw>(m_Scene->getMachine());
    initStatisticText();
    createFrame();
    fillButtonsRender();
    m_Mask.create(sloteSize.x * m_MachineDraw->getCountSlots() + sloteOutlineThickness * (m_MachineDraw->getCountSlots() + 1),
        sloteSize.y + sloteOutlineThickness * 2);
}

void DrawScene::draw(RenderWindow& window)
{
    updateStatistic(m_MachineDraw->getStatistic());
	m_Mask.clear(transparent);
	m_MachineDraw->draw(m_Mask);
    for (const auto& frame : m_SloteFrame)
    {
        m_Mask.draw(frame);
    }
    m_Mask.display();
    Sprite sprite(m_Mask.getTexture());
    sprite.setPosition(slotePos.x - sloteOutlineThickness, slotePos.y - sloteOutlineThickness);
    window.draw(sprite);
    for (const auto& buttonRedner : m_Buttons)
    {
        buttonRedner.draw(window);
    }
    window.draw(m_WinText);
    window.draw(m_BalanceText);
    window.draw(m_BetText);
}

void DrawScene::createFrame()
{
    for (int i = 0; i < m_MachineDraw->getCountSlots(); ++i)
    {
        RectangleShape slote;
        slote.setSize(sloteSize);
        slote.setPosition(sloteOutlineThickness + i * (sloteSize.x + sloteOutlineThickness), sloteOutlineThickness);
        slote.setOutlineThickness(sloteOutlineThickness);
        slote.setOutlineColor(darkBlue);
        slote.setFillColor(transparent);
        m_SloteFrame.emplace_back(move(slote));
    }
}

void DrawScene::initStatisticText()
{
    m_WinText.setFont(ResourceManager::getInstance().getFont());
    m_WinText.setFillColor(darkGray);
    m_WinText.setCharacterSize(winTextSize);
    m_WinText.setPosition(winTextPos);

    m_BalanceText.setFont(ResourceManager::getInstance().getFont());
    m_BalanceText.setFillColor(darkGray);
    m_BalanceText.setCharacterSize(balanceTextSize);
    m_BalanceText.setPosition(balanceTextPos);

    m_BetText.setFont(ResourceManager::getInstance().getFont());
    m_BetText.setFillColor(darkGray);
    m_BetText.setCharacterSize(betTextSize);
    m_BetText.setPosition(betTextPos);
}

void DrawScene::updateStatistic(Statistic& statistic)
{
    m_BetText.setString("Bet: " + to_string(statistic.getBet()));
    m_BalanceText.setString("Balance: " + to_string(statistic.getBalance()));
    m_WinText.setString("Win: " + to_string(statistic.getWin()));
}

void DrawScene::fillButtonsRender()
{
    for (auto& button : m_Scene->getButtons())
    {
        m_Buttons.emplace_back(button);
    }
}
