#include "Button.h"

using namespace std;
using namespace sf;

Button::Button() = default;

Button::~Button() = default;

vector<Drawable*> Button::getElements() const
{
	return m_ElementsButton;
}
