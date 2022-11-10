#include "GoblinGrunt.h"

GoblinGrunt::GoblinGrunt()
{
	m_Texture.loadFromFile("graphics/GoblinGrunt.png");
	m_Sprite.setTexture(m_Texture);
	m_Speed = 200;
	m_Health = 0;
	m_DamageOutput = 0;
	m_mitigation = 0;
}