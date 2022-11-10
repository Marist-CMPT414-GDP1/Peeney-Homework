#include "GoblinBruiser.h"

GoblinBruiser::GoblinBruiser()
{
	m_Texture.loadFromFile("graphics/GoblinBruiser.png");
	m_Sprite.setTexture(m_Texture);
	m_Speed = 100;
	m_Health = 0;
	m_DamageOutput = 0;
	m_mitigation = 0;
}