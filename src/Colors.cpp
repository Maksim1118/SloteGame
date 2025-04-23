#include "Colors.h"

using namespace sf;

const Color darkBlue = { 0, 0, 139 };
const Color transparent = { 0, 0, 0, 0 };
const Color purple = { 166, 0, 247 };
const Color pink = { 252, 15, 192 };
const Color blue = { 13, 64, 216 };
const Color red = { 255, 0, 0 };
const Color cornflowerBlue = {100,149, 237};
const Color cyan = {0, 255, 255};
const Color white = { 255, 255, 255 };
const sf::Color darkGray = {40, 40,40};
const sf::Color lightGray = { 150,150,150 };

const Colors getSymbolColors()
{
	return { purple, pink, blue, red };
}
