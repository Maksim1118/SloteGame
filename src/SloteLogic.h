#pragma once
#include <vector>
#include "MyShape.h"

enum class SloteState
{
	accelerate,
	deccelerate,
	correctPos
};

class SloteLogic
{
public:
	SloteLogic(std::vector<MyShape*> symbols);
	~SloteLogic();
	void setAccelerate(const float accelerate);
	void spin(float diff);
	void startSpin();
	void stopSpin();
	bool isSpinStoped();
	std::vector<MyShape*>& getSymbols();
	float getOffsetY() const;
	MyShape* getSymbol(int index) const;
private:
	void accelerating(float diff);
	void deccelerating(float diff);
	void updateOffset(float diff);
	void correctPos(float diff);

	bool isAccelerate();
	bool isDeccelerate();
	SloteState m_State;

	bool m_IsCorrectPos;
	float m_A;
	float m_V;
	float m_PosY;

	std::vector<MyShape*> m_Symbols;
};