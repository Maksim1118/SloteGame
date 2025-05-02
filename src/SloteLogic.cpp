#include "SloteLogic.h"

#include <iostream>

using namespace std;

const float MAX_SPEED = 25.f;
const float koefDeccelerate = 15.f;

bool isPosDiffcalc = false;

SloteLogic::SloteLogic(vector<MyShape*> symbols)
	:m_Symbols(symbols) , m_A(0.f), m_V(0.f), m_PosY(0.f), m_IsCorrectPos(true), m_State(SloteState::accelerate)
{
}

SloteLogic::~SloteLogic()
{
	for (const auto& symbol : m_Symbols)
	{
		delete symbol;
	}
	m_Symbols.clear();
}

void SloteLogic::setAccelerate(const float accelerate)
{
	m_A = accelerate;
}

vector<MyShape*>& SloteLogic::getSymbols()
{
	return m_Symbols;
}

float SloteLogic::getOffsetY() const
{
	return m_PosY;
}

void SloteLogic::spin(float diff)
{
	switch (m_State)
	{
		case SloteState::accelerate:
		{
			m_IsCorrectPos = false;
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
			break;
		}
		default:
			break;
	}
}

bool SloteLogic::isSpinStoped()
{
	return m_IsCorrectPos;
}

void SloteLogic::startSpin()
{
	m_State = SloteState::accelerate;
}

void SloteLogic::stopSpin()
{
	m_State = SloteState::deccelerate;
}

MyShape* SloteLogic::getSymbol(int index) const
{
	int offsetIndex = 4 - round(m_PosY);
	int adjustIndex = (index + offsetIndex) % m_Symbols.size();
	return m_Symbols[adjustIndex];
}

void SloteLogic::accelerating(float diff)
{
	m_V += m_A * diff;
}

void SloteLogic::deccelerating(float diff)
{
	m_V -= m_A * diff;
}

bool SloteLogic::isAccelerate()
{
	if (m_V > MAX_SPEED)
	{
		m_V = MAX_SPEED;
		return false;
	};
	return true;
}

bool SloteLogic::isDeccelerate()
{
	if (m_V < 0.9f)
	{
		m_V = 0.9f;
		return false;
	}
	return true;
}

void SloteLogic::updateOffset(float diff)
{
	m_PosY += diff;
	if (m_PosY >= m_Symbols.size())
	{
		m_PosY -= m_Symbols.size();
	}
}

void SloteLogic::correctPos(float diff)
{
	float posDiff = ceil(m_PosY) - m_PosY;

	if (fabs(posDiff) < 0.001f)
	{
		m_V = 0.f;
		m_IsCorrectPos = true;
		return;
	}
	const float k = 0.06f;
	const float k2 = 2e-05;

	m_V *= exp(-k * diff) - m_V * k2 * fabs(posDiff);

	if (m_V < 0.05f)
		m_V = 0.05f;
	float step = std::min(fabs(m_V * diff), fabs(posDiff));
	updateOffset((posDiff > 0) ? step : -step);
}

