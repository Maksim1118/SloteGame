#include <SFML/Graphics.hpp>
#include <vector>

#include "Variables.h"
#include "Colors.h"

using namespace sf;
using namespace std;

const size_t SCREEN_W = 1920;
const size_t SCREEN_H = 1080;

int main() 
{
    RenderWindow window({ SCREEN_W, SCREEN_H }, "SloteGame", Style::Close | Style::Titlebar);

    vector<RectangleShape> sloteFrame;
    for (int i = 0; i < countSlotes; ++i)
    {
        RectangleShape slote;
        slote.setSize(sloteSize);
        slote.setPosition(
            (SCREEN_W - sloteSize.x * countSlotes ) / 2.f + i * (sloteSize.x + sloteOutlineThickness),
            (SCREEN_H - sloteSize.y) / 2.f);
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
        window.display();
    }
}
