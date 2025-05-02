#include "SloteDraw.h"

#include "Colors.h"
#include "Variables.h"
#include "SloteLogic.h"


using namespace sf;

static int nextId = 0;

const float topMargin = 20.f;
const float bottomMargin = 20.f;


SloteDraw::SloteDraw(SloteLogic* sloteLogic)
	:m_SloteLogic(sloteLogic), m_Id(nextId++)
{
	m_Symbols = sloteLogic->getSymbols();
	size_t countSymbols = m_Symbols.size();
	float totalHeight = symbolSize * m_Symbols.size();
	float emptySpace = sloteSize.y - totalHeight;

	m_SymbolMargin = emptySpace / countSymbols;
	setPosition();
}

SloteDraw::~SloteDraw()
{

}


void SloteDraw::setPosition()
{

	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		float posX = (sloteSize.x - symbolSize) / 2.f + m_Id * (sloteSize.x + sloteOutlineThickness);
		float posY = calcY(i);
		m_Symbols[i]->setPosition({ posX, posY });
	}
}

float SloteDraw::calcY(float numPos) const
{
	return sloteOutlineThickness + m_SymbolMargin / 2.f + numPos * (symbolSize + m_SymbolMargin);
}

void SloteDraw::draw(RenderTarget& target) const
{
	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		float numPos = i + m_SloteLogic->getOffsetY();
		if (numPos > m_Symbols.size())
		{
			numPos -= m_Symbols.size();
		}
		float yPos = calcY(numPos);
		m_Symbols[i]->setPosition({ m_Symbols[i]->getPosition().x, yPos });
		target.draw(*m_Symbols[i]);
		if (numPos > m_Symbols.size() - 1)
		{
			numPos -= m_Symbols.size();
			float yPos = calcY(numPos);
			m_Symbols[i]->setPosition({ m_Symbols[i]->getPosition().x, yPos });
			target.draw(*m_Symbols[i]);
		}
	}
}
