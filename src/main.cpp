#include <SFML/Graphics.hpp>
#include <vector>

#include "GameScene.h"
#include "DrawScene.h"
#include "Colors.h"

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace sf;
using namespace std;

const size_t SCREEN_W = 1920;
const size_t SCREEN_H = 1080;


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#else
int main()
#endif
{
    RenderWindow window({ SCREEN_W, SCREEN_H }, "SloteGame", Style::Close | Style::Titlebar);
    window.setFramerateLimit(100);

    GameScene scene;
    DrawScene drawScene(&scene);

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
            scene.hangleEvent(event, mousePos);
        }
        float deltaTime = clock.restart().asSeconds();
        scene.timeElapsed(deltaTime, mousePos);

        window.clear(cyan);
        drawScene.draw(window);
        window.display();
    }
    return 0;
}
