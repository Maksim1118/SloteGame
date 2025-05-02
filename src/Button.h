#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Button
{
public:
    Button();
    virtual ~Button();
    virtual void update(const sf::Vector2f mousePos) = 0;
    virtual std::vector<sf::Drawable*> getElements() const;
protected:
    virtual bool isPos(const sf::Vector2f mousePos) const = 0;
    std::vector<sf::Drawable*> m_ElementsButton;
};
