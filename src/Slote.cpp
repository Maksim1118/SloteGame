#include "Slote.h"

#include <stdexcept>

#include "Colors.h"
#include "Variables.h"


using namespace sf;
using namespace std;

static int nextId = 0;

Slote::Slote()
	:m_Id(nextId++)
{
}

Slote::~Slote()
{
	for (const auto& symbol : m_Symbols)
	{
		delete symbol;
	}
}

void Slote::setSymbols(std::vector<MyShape*>& symbols)
{
	m_Symbols = symbols;
	setPosition();
}

void Slote::setPosition()
{
	size_t countSymbols = m_Symbols.size();
	float totalHeight = symbolSize * m_Symbols.size();
	float emptySpace = (sloteSize.y - totalHeight);

	float margin = emptySpace / (countSymbols + 1);

	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		float posX = slotePos.x + (sloteSize.x - symbolSize) / 2.f + m_Id * (sloteSize.x + sloteOutlineThickness);
		float posY = slotePos.y  + margin * (i+1) + i * symbolSize;
		m_Symbols[i]->setPosition({posX, posY});
	}
}

void Slote::draw(RenderTarget& target) const
{
	for (const auto& symbol : m_Symbols)
	{
		target.draw(*symbol);
	}
}
