#include "GoblinBruiser.h"

GoblinBruiser::GoblinBruiser()
{
	m_Texture.loadFromFile("graphics/GoblinBruiser.png");
	m_Sprite.setTexture(m_Texture);
	m_Speed = 100;
	m_Health = 5;
	m_DamageOutput = 5;
	m_Mitigation = 2;
}