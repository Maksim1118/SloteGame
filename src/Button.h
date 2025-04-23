#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button() = default;
    virtual ~Button() = default;
    virtual void update(const sf::Vector2f mousePos) = 0;
    virtual void draw(sf::RenderTarget& target) = 0;
protected:
    virtual bool isPos(const sf::Vector2f mousePos) const = 0;
};
