#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Button.h"

class TextButton : public Button
{
public:
	TextButton(const std::string& str);
	void setText(const std::string& str);
	void setTextColor(const sf::Color& color);
	void setTextSize(unsigned int size);
	void setTextFont(const sf::Font& font);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f pos);
	void setFrameColor(sf::Color color);
	void update(const sf::Vector2f mousePos) override;
	bool isPos(const sf::Vector2f mousePos) const override;
private:
	void textPos();
	sf::RectangleShape m_Shape;
	sf::Text m_Text;

	sf::Color m_NormalColor;
	bool m_IsHovered;
};