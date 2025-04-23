#pragma once
#include <SFML/Graphics.hpp>

#include "Button.h"

class TextButton : public Button
{
public:
	TextButton(sf::Text& text);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);
	void setColor(sf::Color color);
	void update(const sf::Vector2f mousePos) override;
	void draw(sf::RenderTarget& target) override;
private:
	bool isPos(const sf::Vector2f mousePos) const override;
	void textPos();
	sf::RectangleShape m_Shape;

	sf::Color m_NormalColor;
	bool m_IsHovered;
	sf::Text& m_Text;
};