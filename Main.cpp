#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

class Arrow
{
private:
	Vector2f pos;
	float dx;
	float dy;
	Texture tex;
	Sprite pSprite;
	IntRect texArrow;
public:
	Arrow(float x_in, float y_in)
	{
		pos.x = x_in;
		pos.y = y_in;
		dx = 20;
		dy = 20;
		tex.loadFromFile("strzalka.png");
		pSprite.setTexture(tex);
		pSprite.setPosition(pos);
		IntRect texArrow(80, 0, 80, 80);
		pSprite.setTextureRect(texArrow);
	}
	Sprite getArrow() { return pSprite; }
	void przesun(float x_in, float y_in)
	{
		Vector2f por;
		por.x = x_in;
		por.y = y_in;
		pSprite.move(por);
		pos = pSprite.getPosition();
	}
	void animuj() 
	{

	}
};

class meteor {
private:
	Vector2f pos;
	float dx;
	float dy;
	Texture tex;
	Sprite pSprite;
public:

};


int main()
{
	RenderWindow window(VideoMode(1300, 950), "VectorSpeed");
	Arrow player(610,435);
	Clock zegar;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);
		window.draw(player.getArrow());
		window.display();
		if (zegar.getElapsedTime().asMilliseconds() > 5.0f)
		{
			player.animuj();
			zegar.restart();
		}
	}

	return 0;
}