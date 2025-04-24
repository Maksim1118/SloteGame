#include "Slote.h"

#include <stdexcept>
#include <iostream>

#include "Colors.h"
#include "Variables.h"


using namespace sf;
using namespace std;

static int nextId = 0;
const float MAX_SPEED = 15.f;
const float koefDeccelerate = 15.f;

const float topMargin = 20.f;
const float bottomMargin = 20.f;


Slote::Slote(std::vector<MyShape*>& symbols)
	:m_Symbols(symbols), m_Id(nextId++), m_A(0.f), m_V(0.f), m_PosY(0.f), m_IsCorrectPos(true), m_IsSpinning(false)
{
	size_t countSymbols = m_Symbols.size();
	float totalHeight = symbolSize * m_Symbols.size();
	float emptySpace = sloteSize.y - totalHeight;

	m_SymbolMargin = emptySpace / countSymbols;
	setPosition();
}

Slote::~Slote()
{
	for (const auto& symbol : m_Symbols)
	{
		delete symbol;
	}
}

void Slote::setAccelerate(const float accelerate)
{
	m_A = accelerate;
}

void Slote::spin(float diff)
{
	if (m_IsSpinning)
	{
		switch (m_State)
		{
		case SloteState::accelerate:
		{
			accelerating(diff);
			if (!isAccelerate())
			{
				m_State = SloteState::deccelerate;
			}
			else
			{
				updateOffset(m_V * diff);
			}
			break;
		}
		case SloteState::deccelerate:
		{
			deccelerating(diff * koefDeccelerate);
			if (!isDeccelerate())
			{
				m_State = SloteState::correctPos;
			}
			else
			{
				updateOffset(m_V * diff);
			}
			break;
		}
		case SloteState::correctPos:
		{
			correctPos(diff);
			if (m_IsCorrectPos)
			{
				m_IsSpinning = false;
			}
			break;
		}
		default:
			break;
		}
	}
}

bool Slote::isSpinStoped()
{
	return m_IsCorrectPos;
}

void Slote::startSpin()
{
	m_IsSpinning = true;
	m_IsCorrectPos = false;
	m_State = SloteState::accelerate;
}

void Slote::stopSpin()
{
	m_State = SloteState::deccelerate;
}


void Slote::setPosition()
{

	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		float posX = (sloteSize.x - symbolSize) / 2.f + m_Id * (sloteSize.x + sloteOutlineThickness);
		float posY = calcY(i);
		m_Symbols[i]->setPosition({posX, posY});
	}
}

void Slote::accelerating(float diff)
{
	m_V += m_A * diff;
}

void Slote::deccelerating(float diff)
{
	m_V -= m_A * diff;
}

bool Slote::isAccelerate()
{
	if (m_V > MAX_SPEED)
	{
		m_V = MAX_SPEED;
		return false;
	};
	return true;
}

bool Slote::isDeccelerate()
{
	if (m_V < 0.9f)
	{
		return false;
	}
	return true;
}

void Slote::updateOffset(float diff)
{
	m_PosY += diff;
	if (m_PosY >= m_Symbols.size())
	{
		m_PosY -= m_Symbols.size();
	}
}

void Slote::correctPos(float diff)
{
	float posDiff = ceil(m_PosY) - m_PosY;
	if (fabs(posDiff) < 0.001f)
	{
		m_V = 0.f;
		m_IsCorrectPos = true;
		return;
	}
	float correct = min(fabs(m_V * diff), fabs(posDiff));
	updateOffset((posDiff > 0)? correct : -correct);
}

float Slote::calcY(float numPos) const
{
	return sloteOutlineThickness + m_SymbolMargin/2.f + numPos * (symbolSize + m_SymbolMargin);
}

void Slote::draw(RenderTarget& target) const
{
	for (int i = 0; i < m_Symbols.size(); ++i)
	{
		float numPos = i + m_PosY;
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
