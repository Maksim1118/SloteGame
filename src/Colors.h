#pragma once
#include <SFML/Graphics.hpp>
#include <array>

extern const sf::Color darkBlue;
extern const sf::Color transparent;
extern const sf::Color red;
extern const sf::Color purple;
extern const sf::Color pink;
extern const sf::Color blue;

using Colors = std::array<sf::Color, 4>;

const Colors getSymbolColors();
