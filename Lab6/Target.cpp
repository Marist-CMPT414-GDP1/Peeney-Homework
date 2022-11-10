#include <SFML/Graphics.hpp>
using namespace sf;

class Target
{
private:
	RectangleShape m_Shape;
	float m_Health = 10;

public:
	Target();
};

Target::Target()
{
	m_Shape.setFillColor(Color::White);
	m_Shape.setSize({ 50, 50 });
}