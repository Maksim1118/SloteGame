#include <SFML/Graphics.hpp>
#include <vector>

#include"ResourceManager.h"
#include "Variables.h"
#include "Colors.h"
#include "SloteMachine.h"
#include "Rectangle.h"
#include "TextButton.h"



using namespace sf;
using namespace std;

const size_t SCREEN_W = 1920;
const size_t SCREEN_H = 1080;

int main() 
{
    RenderWindow window({ SCREEN_W, SCREEN_H }, "SloteGame", Style::Close | Style::Titlebar);
    window.setFramerateLimit(100);

    ResourceManager::getInstance().load();

    SloteMachine machine;

    vector<RectangleShape> sloteFrame;
    for (int i = 0; i < machine.getCountSlots(); ++i)
    {
        RectangleShape slote;
        slote.setSize(sloteSize);
        slote.setPosition(sloteOutlineThickness + i * (sloteSize.x + sloteOutlineThickness),sloteOutlineThickness);
        slote.setOutlineThickness(sloteOutlineThickness);
        slote.setOutlineColor(darkBlue);
        slote.setFillColor(transparent);
        sloteFrame.emplace_back(slote);
    }

    RenderTexture mask;
    mask.create(sloteSize.x* machine.getCountSlots() + sloteOutlineThickness * (machine.getCountSlots() + 1), 
        sloteSize.y + sloteOutlineThickness * 2);

    Text startText;
    startText.setString("start");
    startText.setFont(ResourceManager::getInstance().getFont(FontName::START));
    startText.setFillColor(red);
    startText.setCharacterSize(startTextSize);

    TextButton butStart(startText);
    butStart.setPosition(startButtPos);
    butStart.setSize(startButtSize);
    butStart.setColor(lightGray);

    Text stopText;
    stopText.setString("stop");
    stopText.setFont(ResourceManager::getInstance().getFont(FontName::STOP));
    stopText.setFillColor(red);
    stopText.setCharacterSize(stopTextSize);

    TextButton butStop(stopText);
    butStop.setPosition(stopButtPos);
    butStop.setSize(stopButtSize);
    butStop.setColor(lightGray);

    Clock clock;
    Vector2f mousePos;
    while (window.isOpen())
    {
        Event event;
        mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
        machine.run(deltaTime);
        butStart.update(mousePos);
        butStop.update(mousePos);

        window.clear(cyan);
        mask.clear(transparent);
        machine.draw(mask);
        for (const auto& slote : sloteFrame)
        {
            mask.draw(slote);
        }
        mask.display();
        Sprite sprite(mask.getTexture());
        sprite.setPosition(slotePos.x - sloteOutlineThickness, slotePos.y - sloteOutlineThickness);
        window.draw(sprite);
        butStart.draw(window);
        butStop.draw(window);
        window.display();
    }
}
