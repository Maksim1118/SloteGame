#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyShape.h"

enum class SloteState
{
	accelerate,
	deccelerate,
	correctPos
};

class Slote
{
public:
	Slote(std::vector<MyShape*>& symbols);
	~Slote();
	void setAccelerate(const float accelerate);
	void spin(float diff);
	bool isSpinStoped();
	void startSpin();
	void draw(sf::RenderTarget& target) const;
private:
	void setPosition();
	void accelerating(float diff);
	void deccelerating(float diff);

	bool isAccelerate();
	bool isDeccelerate();

	void updateOffset(float diff);
	void correctPos(float diff);
	float calcY(float numPos) const;
	SloteState m_State;

	bool m_IsSpinning;
	int m_Id;
	float m_A;
	float m_V;
	float m_PosY;
	bool m_IsCorrectPos;
	float m_SymbolMargin;
	std::vector<MyShape*> m_Symbols;
};