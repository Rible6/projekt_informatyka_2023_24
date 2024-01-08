#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
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

class Meteor {
private:
	Vector2f pos;
	float dx;
	float dy;
	Texture tex;
	Sprite pSprite;
	IntRect texMeteor;
	random_device rd;
public:
	Meteor()
	{
		mt19937 gen(rd());
		uniform_int_distribution<>distx(200,1100);
		uniform_int_distribution<>distdx(-20,20);
		uniform_int_distribution<>distdy(90,180);
		pos.x = distx(gen);
		pos.y = -200;
		dx = float(distdx(gen))/100;
		dy = float(distdy(gen))/100;
		tex.loadFromFile("strzalka.png");
		pSprite.setTexture(tex);
		pSprite.setPosition(pos);
		texMeteor.left = 0;
		texMeteor.top = 0;
		texMeteor.height = 80;
		texMeteor.width = 80;
		pSprite.setTextureRect(texMeteor);
	}
	Sprite getMeteor() { return pSprite; }
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
		przesun(dx, dy);
	}
	bool usun()
	{
		if (pos.y > 1050) return 1;
		else return 0;
	}
};


int main()
{
	RenderWindow window(VideoMode(1300, 950), "VectorSpeed");
	Event event;
	Arrow player(610, 435);
	Meteor* cd[10] = { nullptr };
	Clock zegar1;
	Clock zegar2;
	Time czas;
	int tim1;
	while (window.isOpen())
	{
		czas = zegar2.getElapsedTime();
		tim1 = czas.asSeconds();
		if (cd[0] == nullptr) cd[0] = new Meteor;
		else if (cd[0]->usun() == 1)
		{
			delete cd[0];
			cd[0] = { nullptr };
		}
		if (cd[1] == nullptr) cd[1] = new Meteor;
		else if (cd[1]->usun() == 1) 
		{
			delete cd[1];
			cd[1] = { nullptr };
		}
		if (cd[2] == nullptr) cd[2] = new Meteor;
		else if (cd[2]->usun() == 1) 
		{
			delete cd[2];
			cd[2] = { nullptr };
		}
		if (tim1 > 10)
		{
			if (cd[3] == nullptr) cd[3] = new Meteor;
			else if (cd[3]->usun() == 1) 
			{
				delete cd[3];
				cd[3] = { nullptr };
			}
			if (tim1 > 15)
			{
				if (cd[4] == nullptr) cd[4] = new Meteor;
				else if (cd[4]->usun() == 1) 
				{
					delete cd[4];
					cd[4] = { nullptr };
				}
				if (tim1 > 20)
				{
					if (cd[5] == nullptr) cd[5] = new Meteor;
					else if (cd[5]->usun() == 1) 
					{
						delete cd[5];
						cd[5] = { nullptr };
					}
					if (tim1 > 25)
					{
						if (cd[6] == nullptr) cd[6] = new Meteor;
						else if (cd[6]->usun() == 1) 
						{
							delete cd[6];
							cd[6] = { nullptr };
						}
						if (tim1 > 30)
						{
							if (cd[7] == nullptr) cd[7] = new Meteor;
							else if (cd[7]->usun() == 1) 
							{
								delete cd[7];
								cd[7] = { nullptr };
							}
							if (tim1 > 35)
							{
								if (cd[8] == nullptr) cd[8] = new Meteor;
								else if (cd[8]->usun() == 1) 
								{
									delete cd[8];
									cd[8] = { nullptr };
								}
								if (tim1 > 40)
								{
									if (cd[9] == nullptr) cd[9] = new Meteor;
									else if (cd[9]->usun() == 1) 
									{
										delete cd[9];
										cd[9] = { nullptr };
									}
								}
							}
						}
					}
				}
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);
		window.draw(player.getArrow());
		if(cd[0]!=nullptr)
		window.draw(cd[0]->getMeteor());
		if (cd[1] != nullptr)
		window.draw(cd[1]->getMeteor());
		if (cd[2] != nullptr)
		window.draw(cd[2]->getMeteor());
		if (cd[3] != nullptr)
		window.draw(cd[3]->getMeteor());
		if (cd[4] != nullptr)
		window.draw(cd[4]->getMeteor());
		if (cd[5] != nullptr)
		window.draw(cd[5]->getMeteor());
		if (cd[6] != nullptr)
		window.draw(cd[6]->getMeteor());
		if (cd[7] != nullptr)
		window.draw(cd[7]->getMeteor());
		if (cd[8] != nullptr)
		window.draw(cd[8]->getMeteor());
		if (cd[9] != nullptr)
		window.draw(cd[9]->getMeteor());
		window.display();
		if (zegar1.getElapsedTime().asMilliseconds() > 5.0f)
		{
			player.animuj();
			if (cd[0] != nullptr)
			cd[0]->animuj();
			if (cd[1] != nullptr)
			cd[1]->animuj();
			if (cd[2] != nullptr)
			cd[2]->animuj();
			if (cd[3] != nullptr)
			cd[3]->animuj();
			if (cd[4] != nullptr)
			cd[4]->animuj();
			if (cd[5] != nullptr)
			cd[5]->animuj();
			if (cd[6] != nullptr)
			cd[6]->animuj();
			if (cd[7] != nullptr)
			cd[7]->animuj();
			if (cd[8] != nullptr)
			cd[8]->animuj();
			if (cd[9] != nullptr)
			cd[9]->animuj();
			zegar1.restart();
		}
	}

	return 0;
}