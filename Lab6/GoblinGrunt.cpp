#include "GoblinGrunt.h"

GoblinGrunt::GoblinGrunt()
{
	m_Texture.loadFromFile("graphics/GoblinGrunt.png");
	m_Sprite.setTexture(m_Texture);
	m_Speed = 200;
	m_Health = 10;
	m_DamageOutput = 1;
	m_Mitigation = 1;
}