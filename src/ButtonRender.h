#pragma once
#include <SFML/Graphics.hpp>

class Button;

class ButtonRender
{
public:
    ButtonRender(Button* button);
    ~ButtonRender();
    void draw(sf::RenderTarget& target) const;
private:
    Button* m_Button;
};
