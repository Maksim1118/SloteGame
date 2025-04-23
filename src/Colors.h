#pragma once
#include <SFML/Graphics.hpp>
#include <array>

extern const sf::Color darkBlue;
extern const sf::Color transparent;
extern const sf::Color red;
extern const sf::Color purple;
extern const sf::Color pink;
extern const sf::Color blue;
extern const sf::Color cornflowerBlue;
extern const sf::Color cyan;
extern const sf::Color white;
extern const sf::Color darkGray;
extern const sf::Color lightGray;

using Colors = std::array<sf::Color, 4>;

const Colors getSymbolColors();
