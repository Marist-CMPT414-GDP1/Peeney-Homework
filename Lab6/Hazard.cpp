#include <SFML/Graphics.hpp>
using namespace sf;

class Hazard
{
private:
	RectangleShape m_Shape;

public:
	Hazard();
};

Hazard::Hazard() 
{
	m_Shape.setFillColor(Color::Red);
	m_Shape.setSize({100, 100});
}