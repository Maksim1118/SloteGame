#include "TextButton.h"
#include "Colors.h"
#include "ResourceManager.h"

using namespace sf;
using namespace std;

const Vector2f startSize = { 170.f, 70.f };
const float blackOut = 0.4f;
const float startButtonTextSize = 25.f;

TextButton::TextButton(const string& str)
    :m_IsHovered(false)
{
    m_Text.setString(str);
    m_Text.setFont(ResourceManager::getInstance().getFont());
    m_Text.setCharacterSize(startButtonTextSize);
    setTextColor(red);

    setFrameColor(lightGray);

    setSize(startSize);
    m_ElementsButton.emplace_back(&m_Shape);
    m_ElementsButton.emplace_back(&m_Text);
}

void TextButton::setText(const string& str)
{
    m_Text.setString(str);
    textPos();
}

void TextButton::setTextColor(const Color& color)
{
    m_Text.setFillColor(color);
}

void TextButton::setTextSize(unsigned int size)
{
    m_Text.setCharacterSize(size);
    textPos();
}

void TextButton::setTextFont(const sf::Font& font)
{
    m_Text.setFont(font);
    textPos();
}

bool TextButton::isPos(const sf::Vector2f mousePos) const
{
    Vector2f butPos = m_Shape.getPosition();
    FloatRect butSize = m_Shape.getLocalBounds();
    return mousePos.x > butPos.x && mousePos.x < butPos.x + butSize.width
        && mousePos.y > butPos.y && mousePos.y < butPos.y + butSize.height;
}

void TextButton::setSize(sf::Vector2f size)
{
    m_Shape.setSize(size);
    textPos();
}

void TextButton::setPosition(sf::Vector2f pos)
{
    m_Shape.setPosition(pos);
    textPos();
}

void TextButton::setFrameColor(sf::Color color)
{
    m_Shape.setFillColor(color);
    m_NormalColor = color;
}

void TextButton::update(const sf::Vector2f mousePos)
{
    if (isPos(mousePos))
    {
        if (!m_IsHovered)
        {
            Color color = m_Shape.getFillColor();
            color.r = static_cast<Uint8>(color.r * blackOut);
            color.g = static_cast<Uint8>(color.g * blackOut);
            color.b = static_cast<Uint8>(color.b * blackOut);
            m_Shape.setFillColor(color);
            m_IsHovered = true;
        }
    }
    else
    {   
        if (m_IsHovered)
        {
            m_Shape.setFillColor(m_NormalColor);
            m_IsHovered = false;
        }
    }
}

void TextButton::textPos()
{
    Vector2f pos;
    pos.x = m_Shape.getPosition().x + (m_Shape.getLocalBounds().width - m_Text.getLocalBounds().width) / 2.f;
    pos.y = m_Shape.getPosition().y + (m_Shape.getLocalBounds().height - m_Text.getLocalBounds().height - m_Text.getCharacterSize()/2.f) / 2.f;
    m_Text.setPosition(pos);
}
