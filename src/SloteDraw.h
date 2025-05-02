#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MyShape.h"
class SloteLogic;

class SloteDraw
{
public:
	SloteDraw(SloteLogic* sloteLogic);
	~SloteDraw();
	void draw(sf::RenderTarget& target) const;
private:
	SloteLogic* m_SloteLogic;
	void setPosition();
	float calcY(float numPos) const;
	float m_SymbolMargin;
	int m_Id;
	std::vector<MyShape*> m_Symbols;
};