#include "GameScene.h"

#include "ResourceManager.h"
#include "Colors.h"
#include "Variables.h"

using namespace sf;
using namespace std;

GameScene::GameScene()
{
    ResourceManager::getInstance().load();
    initButtons();
    m_MachineLogic = make_unique<SloteMachineLogic>();
}

GameScene::~GameScene()
{
    for (const auto& button : m_Buttons)
    {
        delete button;
    }
    m_Buttons.clear();
}

void GameScene::timeElapsed(float diff, Vector2f mousePos)
{
	m_MachineLogic->run(diff);
    updateButtons(mousePos);
}

void GameScene::hangleEvent(Event& event, Vector2f mousePos)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
    {
        if (m_StartButton->isPos(mousePos))
        {
            m_MachineLogic->start();
        }

        else if (m_StopButton->isPos(mousePos))
        {
            m_MachineLogic->stop();
        }
    }
}

SloteMachineLogic* GameScene::getMachine()
{
    return m_MachineLogic.get();
}

std::vector<Button*>& GameScene::getButtons()
{
    return m_Buttons;
}

void GameScene::initButtons()
{
    m_StartButton = new TextButton("start");
    m_StartButton->setPosition(startButtPos);
    m_Buttons.emplace_back(m_StartButton);

    m_StopButton = new TextButton("stop");
    m_StopButton->setPosition(stopButtPos);
    m_Buttons.emplace_back(m_StopButton);
}

void GameScene::updateButtons(Vector2f mousePos)
{
    m_StartButton->update(mousePos);
    m_StopButton->update(mousePos);
}

