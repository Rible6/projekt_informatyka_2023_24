#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

Event event;

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
		dx = 2;
		dy = 2;
		tex.loadFromFile("strzalka.png");
		pSprite.setTexture(tex);
		pSprite.setPosition(pos);
		texArrow.left=0;
		texArrow.top = 0;
		texArrow.height = 80;
		texArrow.width = 80;
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
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			przesun(dx, -dy);
			texArrow.left = 160;
			texArrow.top = 80;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
		{
			przesun(-dx, -dy);
			texArrow.left = 160;
			texArrow.top = 160;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
		{
			przesun(dx, dy);
			texArrow.left = 80;
			texArrow.top = 80;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			przesun(-dx, dy);
			texArrow.left = 80;
			texArrow.top = 160;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			przesun(0, -dy);
			texArrow.left = 160;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			przesun(0, dy);
			texArrow.left = 80;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			przesun(-dx, 0);
			texArrow.top = 160;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			przesun(dx, 0);
			texArrow.top = 80;
		}
		pSprite.setTextureRect(texArrow);
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