#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
using namespace std;
using namespace sf;

Font font;
int punkt = 0;
int tim1 = 0;
int tim0 = 0;
int punkt0 = 0;

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

	void odczyt()
	{
		FILE* fp;
		fp = fopen("zapis.dat", "a+");
		fseek(fp, 0, SEEK_SET);
		fread(&punkt0, sizeof(int), 1, fp);
		fread(&tim0, sizeof(int), 1, fp);
		fread(&pos, sizeof(Vector2f), 1, fp);
		pSprite.setPosition(pos);
		fclose(fp);
	}

	void przesun(float x_in, float y_in)
	{
		Vector2f por;
		por.x = x_in;
		por.y = y_in;
		if (pos.x < 0 && x_in<0)
		{
			por.x = 0;
		}
		if (pos.x>1221 && x_in > 0)
		{
			por.x = 0;
		}
		if (pos.y < 0 && y_in < 0)
		{
			por.y = 0;
		}
		if (pos.y > 870 && y_in > 0)
		{
			por.y = 0;
		}
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
		tex.loadFromFile("meteo.png");
		pSprite.setTexture(tex);
		pSprite.setPosition(pos);
		texMeteor.left = 0;
		texMeteor.top = 0;
		texMeteor.height = 120;
		texMeteor.width = 120;
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
		if (pos.y > 1050) return true;
		else return false;
	}
};

void koniec(Sprite getarrow, Sprite getmeteor, RenderWindow& window)
{
	FloatRect arrow = getarrow.getGlobalBounds();
	FloatRect meteor = getmeteor.getGlobalBounds();
	float x = (getarrow.getPosition().x + (arrow.width / 2)-5) - (getmeteor.getPosition().x + (meteor.width / 2));
	float y= (getarrow.getPosition().y+7 + (arrow.height / 2)-5) - (getmeteor.getPosition().y + (meteor.height / 2));
	float distance = sqrt((x * x) + (y * y));
	if (distance <=(arrow.width/2)-5+(meteor.width/2))
	{
		Text text("KONIEC GRY!", font, 60);
		text.setFillColor(Color::Black);
		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		window.draw(text);
		window.display();
		sleep(seconds(2));
		window.close();
	}
}

void zapis(Vector2f xy)
{
	FILE* fp;
	fp = fopen("zapis.dat", "w+");
	fseek(fp, 0, SEEK_SET);
	fwrite(&punkt, sizeof(int), 1, fp);
	fwrite(&tim1, sizeof(int), 1, fp);
	fwrite(&xy, sizeof(Vector2f), 1, fp);
	fclose(fp);
}

int main()
{
	RenderWindow window(VideoMode(1300, 950), "VectorSpeed");
	Event event;
	font.loadFromFile("AlienRavager.ttf");
	Text punkty;
	punkty.setFont(font);
	punkty.setCharacterSize(30);
	punkty.setFillColor(sf::Color::Black);
	punkty.setPosition(10,10);
	Arrow player(610, 435);
	Meteor* cd[10] = { nullptr };
	Clock zegar1;
	Clock zegar2;
	Time czas;
	player.odczyt();
	while (window.isOpen())
	{
		czas = zegar2.getElapsedTime();
		tim1 = tim0 + czas.asSeconds();
		punkt = punkt0 + czas.asSeconds() * 12;
		zapis(player.getArrow().getPosition());
		punkty.setString("Score: " + to_string(punkt) + "\n"+"Czas: " + to_string(tim1));
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
		window.draw(punkty);
		window.draw(player.getArrow());
		if (cd[0] != nullptr)
		{
			window.draw(cd[0]->getMeteor());
			koniec(player.getArrow(), cd[0]->getMeteor(), window);
		}
		if (cd[1] != nullptr)
		{
			window.draw(cd[1]->getMeteor());
			koniec(player.getArrow(), cd[1]->getMeteor(), window);
		}
		if (cd[2] != nullptr)
		{
			window.draw(cd[2]->getMeteor());
			koniec(player.getArrow(), cd[2]->getMeteor(), window);
		}
		if (cd[3] != nullptr)
		{
			window.draw(cd[3]->getMeteor());
			koniec(player.getArrow(), cd[3]->getMeteor(), window);
		}
		if (cd[4] != nullptr)
		{
			window.draw(cd[4]->getMeteor());
			koniec(player.getArrow(), cd[4]->getMeteor(), window);
		}
		if (cd[5] != nullptr)
		{
			window.draw(cd[5]->getMeteor());
			koniec(player.getArrow(), cd[5]->getMeteor(), window);
		}
		if (cd[6] != nullptr)
		{
			window.draw(cd[6]->getMeteor());
			koniec(player.getArrow(), cd[6]->getMeteor(), window);
		}
		if (cd[7] != nullptr)
		{
			window.draw(cd[7]->getMeteor());
			koniec(player.getArrow(), cd[7]->getMeteor(), window);
		}
		if (cd[8] != nullptr)
		{
			window.draw(cd[8]->getMeteor());
			koniec(player.getArrow(), cd[8]->getMeteor(), window);
		}
		if (cd[9] != nullptr)
		{
			window.draw(cd[9]->getMeteor());
			koniec(player.getArrow(), cd[9]->getMeteor(), window);
		}
		window.display();
		if (zegar1.getElapsedTime().asMilliseconds() > 5.0f)
		{
			player.animuj();
			if (cd[0] != nullptr) cd[0]->animuj();
			if (cd[1] != nullptr) cd[1]->animuj();
			if (cd[2] != nullptr) cd[2]->animuj();
			if (cd[3] != nullptr) cd[3]->animuj();
			if (cd[4] != nullptr) cd[4]->animuj();
			if (cd[5] != nullptr) cd[5]->animuj();
			if (cd[6] != nullptr) cd[6]->animuj();
			if (cd[7] != nullptr) cd[7]->animuj();
			if (cd[8] != nullptr) cd[8]->animuj();
			if (cd[9] != nullptr) cd[9]->animuj();
			zegar1.restart();
		}
	}

	return 0;
}
