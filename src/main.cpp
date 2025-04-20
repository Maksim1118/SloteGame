#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>

#include "Variables.h"
#include "Colors.h"
#include "SloteMachine.h"
#include "Rectangle.h"

using namespace sf;
using namespace std;

const size_t SCREEN_W = 1920;
const size_t SCREEN_H = 1080;

int main() 
{
    RenderWindow window({ SCREEN_W, SCREEN_H }, "SloteGame", Style::Close | Style::Titlebar);
    srand(time(nullptr));

    SloteMachine machine;

    vector<RectangleShape> sloteFrame;
    for (int i = 0; i < machine.getCountSlots(); ++i)
    {
        RectangleShape slote;
        slote.setSize(sloteSize);
        slote.setPosition(
            slotePos.x + i * (sloteSize.x + sloteOutlineThickness),
            slotePos.y);
        slote.setOutlineThickness(sloteOutlineThickness);
        slote.setOutlineColor(darkBlue);
        slote.setFillColor(transparent);
        sloteFrame.emplace_back(slote);
    }
   
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear(Color::Cyan);
        for (const auto& slote : sloteFrame)
        {
            window.draw(slote);
        }
        machine.draw(window);
        window.display();
    }
}
