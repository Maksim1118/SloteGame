#include "ButtonRender.h"

#include "Button.h"

ButtonRender::ButtonRender(Button* button)
	:m_Button(button)
{

}

ButtonRender::~ButtonRender()
{
	
}

void ButtonRender::draw(sf::RenderTarget& target) const
{
	for (auto& element : m_Button->getElements())
	{
		target.draw(*element);
	}
}
