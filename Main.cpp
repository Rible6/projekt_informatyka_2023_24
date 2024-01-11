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

Event event;
Font font;

void menu(RenderWindow& window);
void zapis(Vector2f xy, int tim1, int punkt,bool tryb);

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

	void odczyt(int& punkt0, int& tim0,bool& tryb)
	{
		FILE* fp;
		fp = fopen("zapis.dat", "a+");
		fseek(fp, 0, SEEK_SET);
		fread(&punkt0, sizeof(int), 1, fp);
		fread(&tim0, sizeof(int), 1, fp);
		fread(&pos, sizeof(Vector2f), 1, fp);
		fread(&tryb, sizeof(bool), 1, fp);
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
		else 
		{
			texArrow.top = 0;
			texArrow.left = 0;
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
		uniform_int_distribution<>distx(80,1100);
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

void przegrana(Sprite getarrow, Sprite getmeteor, RenderWindow& window)
{
	FloatRect arrow = getarrow.getGlobalBounds();
	FloatRect meteor = getmeteor.getGlobalBounds();
	float x = (getarrow.getPosition().x + (arrow.width / 2)-5) - (getmeteor.getPosition().x + (meteor.width / 2));
	float y= (getarrow.getPosition().y+7 + (arrow.height / 2)-5) - (getmeteor.getPosition().y + (meteor.height / 2));
	float distance = sqrt((x * x) + (y * y));
	if (distance <=(arrow.width/2)-5+(meteor.width/2))
	{
		Text text("KONIEC GRY!", font, 80);
		text.setFillColor(Color::Black);
		FloatRect textBounds = text.getLocalBounds();
		text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		window.draw(text);
		window.display();
		sleep(seconds(2));
		zapis(Vector2f(610, 435), 0, 0, false);
		menu(window);
	}
}

void zapis(Vector2f xy,int tim1,int punkt,bool tryb)
{
	FILE* fp;
	fp = fopen("zapis.dat", "w+");
	fseek(fp, 0, SEEK_SET);
	fwrite(&punkt, sizeof(int), 1, fp);
	fwrite(&tim1, sizeof(int), 1, fp);
	fwrite(&xy, sizeof(Vector2f), 1, fp);
	fwrite(&tryb, sizeof(bool), 1, fp);
	fclose(fp);
}

void F2(RenderWindow& window, Vector2f xy,int tim1,int punkt,bool tryb)
{
	if (Keyboard::isKeyPressed(Keyboard::F2))
	{
		zapis(xy,tim1,punkt,tryb);
		window.close();
	}
}

void F1(RenderWindow& window, Vector2f xy, int tim1, int punkt, bool tryb)
{
	if (Keyboard::isKeyPressed(Keyboard::F1))
	{
		RectangleShape overlay(Vector2f(600, 400));
		overlay.setFillColor(Color(0, 0, 0, 128));
		overlay.setOutlineColor(Color::Black);
		overlay.setOutlineThickness(5);
		overlay.setPosition((window.getSize().x / 2)-300, (window.getSize().y / 2)-300);
		Text text("                                  HELP\nPrzycisk:\n W - poruszanie sie do przodu\n S - poruszanie sie do tylu\n D - poruszanie sie w prawo\n A - poruszanie sie w lewo\n F1 - wyswietlenie ekranu HELP\n F2 - automatyczne zakonczenie\n programu\n ESC - zakonczenie programu\n M - wyjscie do menu", font, 30);
		text.setFillColor(Color::Black);
		text.setPosition((window.getSize().x / 2) - 280, (window.getSize().y / 2) - 280);
		window.draw(overlay);
		window.draw(text);
		window.display();
		sleep(seconds(0.3));
		while (window.isOpen())
		{
			F2(window, xy, tim1, punkt, tryb);
			if (Keyboard::isKeyPressed(Keyboard::F1))
			{
				sleep(seconds(0.2));
				break;
			}
		}
	}
}

void ESC(RenderWindow& window, Vector2f xy, int tim1, int punkt, bool tryb)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		RectangleShape overlay(Vector2f(700, 100));
		overlay.setFillColor(Color(0, 0, 0, 128));
		overlay.setOutlineColor(Color::Black);
		overlay.setOutlineThickness(5);
		overlay.setPosition((window.getSize().x / 2) - 350, (window.getSize().y / 2) - 100);
		Text text("Czy na pewno chcesz opuscic program?\n            [Tak - Enter]             [Nie - Escape]", font, 30);
		text.setFillColor(Color::Black);
		text.setPosition((window.getSize().x / 2) - 320, (window.getSize().y / 2) - 85);
		window.draw(overlay);
		window.draw(text);
		window.display();
		sleep(seconds(0.3));
		while (window.isOpen())
		{
			F2(window, xy, tim1, punkt, tryb);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				zapis(xy, tim1, punkt, tryb);
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) 
			{
				sleep(seconds(0.2));
				break;
			}
		}
	}
}

void M(RenderWindow& window, Vector2f xy, int tim1, int punkt, bool tryb)
{
	if (Keyboard::isKeyPressed(Keyboard::M))
	{
		zapis(xy, tim1, punkt, tryb);
		menu(window);
	}
}

void gra(RenderWindow& window, bool wczyt, bool tryb)
{
	Text punkty;
	punkty.setFont(font);
	punkty.setCharacterSize(30);
	punkty.setFillColor(sf::Color::Black);
	punkty.setPosition(10, 10);
	Arrow player(610, 435);
	Meteor* cd[15] = { nullptr };
	Clock zegar1;
	Clock zegar2;
	Time czas;
	int tim0 = 0;
	int punkt0 = 0;
	float tik = 5.0f;
	if (wczyt == true) player.odczyt(punkt0, tim0, tryb);
	if (tryb == true) tik = 2.5f;
	int tim1;
	int punkt;
	while (window.isOpen())
	{
		czas = zegar2.getElapsedTime();
		tim1 = tim0 + czas.asSeconds();
		punkt = punkt0 + czas.asSeconds() * 12;
		punkty.setString("Score: " + to_string(punkt) + "\nCzas: " + to_string(tim1) + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nF1- HELP");
		F1(window, player.getArrow().getPosition(), tim1, punkt, tryb);
		F2(window, player.getArrow().getPosition(), tim1, punkt, tryb);
		ESC(window, player.getArrow().getPosition(), tim1, punkt, tryb);
		M(window, player.getArrow().getPosition(), tim1, punkt, tryb);
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
									if (tim1 > 45)
									{
										if (cd[10] == nullptr) cd[10] = new Meteor;
										else if (cd[10]->usun() == 1)
										{
											delete cd[10];
											cd[10] = { nullptr };
										}
										if (tim1 > 50)
										{
											if (cd[11] == nullptr) cd[11] = new Meteor;
											else if (cd[11]->usun() == 1)
											{
												delete cd[11];
												cd[11] = { nullptr };
											}
											if (tim1 > 55)
											{
												if (cd[12] == nullptr) cd[12] = new Meteor;
												else if (cd[12]->usun() == 1)
												{
													delete cd[12];
													cd[12] = { nullptr };
												}
												if (tim1 > 60)
												{
													if (cd[13] == nullptr) cd[13] = new Meteor;
													else if (cd[13]->usun() == 1)
													{
														delete cd[13];
														cd[13] = { nullptr };
													}
													if (tim1 > 65)
													{
														if (cd[14] == nullptr) cd[14] = new Meteor;
														else if (cd[14]->usun() == 1)
														{
															delete cd[14];
															cd[14] = { nullptr };
														}
													}
												}
											}
										}
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
			przegrana(player.getArrow(), cd[0]->getMeteor(), window);
		}
		if (cd[1] != nullptr)
		{
			window.draw(cd[1]->getMeteor());
			przegrana(player.getArrow(), cd[1]->getMeteor(), window);
		}
		if (cd[2] != nullptr)
		{
			window.draw(cd[2]->getMeteor());
			przegrana(player.getArrow(), cd[2]->getMeteor(), window);
		}
		if (cd[3] != nullptr)
		{
			window.draw(cd[3]->getMeteor());
			przegrana(player.getArrow(), cd[3]->getMeteor(), window);
		}
		if (cd[4] != nullptr)
		{
			window.draw(cd[4]->getMeteor());
			przegrana(player.getArrow(), cd[4]->getMeteor(), window);
		}
		if (cd[5] != nullptr)
		{
			window.draw(cd[5]->getMeteor());
			przegrana(player.getArrow(), cd[5]->getMeteor(), window);
		}
		if (cd[6] != nullptr)
		{
			window.draw(cd[6]->getMeteor());
			przegrana(player.getArrow(), cd[6]->getMeteor(), window);
		}
		if (cd[7] != nullptr)
		{
			window.draw(cd[7]->getMeteor());
			przegrana(player.getArrow(), cd[7]->getMeteor(), window);
		}
		if (cd[8] != nullptr)
		{
			window.draw(cd[8]->getMeteor());
			przegrana(player.getArrow(), cd[8]->getMeteor(), window);
		}
		if (cd[9] != nullptr)
		{
			window.draw(cd[9]->getMeteor());
			przegrana(player.getArrow(), cd[9]->getMeteor(), window);
		}
		if (cd[10] != nullptr)
		{
			window.draw(cd[10]->getMeteor());
			przegrana(player.getArrow(), cd[10]->getMeteor(), window);
		}
		if (cd[11] != nullptr)
		{
			window.draw(cd[11]->getMeteor());
			przegrana(player.getArrow(), cd[11]->getMeteor(), window);
		}
		if (cd[12] != nullptr)
		{
			window.draw(cd[12]->getMeteor());
			przegrana(player.getArrow(), cd[12]->getMeteor(), window);
		}
		if (cd[13] != nullptr)
		{
			window.draw(cd[13]->getMeteor());
			przegrana(player.getArrow(), cd[13]->getMeteor(), window);
		}
		if (cd[14] != nullptr)
		{
			window.draw(cd[14]->getMeteor());
			przegrana(player.getArrow(), cd[14]->getMeteor(), window);
		}
		window.display();
		if (zegar1.getElapsedTime().asMilliseconds() > tik)
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
			if (cd[10] != nullptr) cd[10]->animuj();
			if (cd[11] != nullptr) cd[11]->animuj();
			if (cd[12] != nullptr) cd[12]->animuj();
			if (cd[13] != nullptr) cd[13]->animuj();
			if (cd[14] != nullptr) cd[14]->animuj();
			zegar1.restart();
		}
	}
}

class Button {
private:
	Text tekst;
	RectangleShape kwad;
public:
	Button(Vector2f pozycja, string tekst1)
	{
		kwad.setSize(Vector2f(200, 50));
		kwad.setFillColor(Color::White);
		kwad.setOutlineColor(Color::Black);
		kwad.setOutlineThickness(5);
		kwad.setPosition(pozycja);

		tekst.setFont(font);
		tekst.setString(tekst1);
		tekst.setCharacterSize(30);
		tekst.setFillColor(Color::Black);
		tekst.setPosition(pozycja.x + 20, pozycja.y + 7);
	}

	RectangleShape getkwad() { return kwad; }
	Text gettekst() { return tekst; }

	bool myszka_nad(RenderWindow& window)
	{
		Vector2i pozycjamysz = Mouse::getPosition(window);
		return kwad.getGlobalBounds().contains(static_cast<Vector2f>(pozycjamysz));
	}

	void zmienkolor(RenderWindow& window)
	{
		if (myszka_nad(window)) kwad.setFillColor(Color::Magenta);
		else kwad.setFillColor(Color::White);
	}

};

void Ustawienia(RenderWindow& window,bool& tryb)
{
	RectangleShape overlay(Vector2f(600, 200));
	RectangleShape kwad1(Vector2f(40, 40));
	RectangleShape kwad2(Vector2f(30, 30));
	kwad1.setPosition(750, 380);
	kwad2.setPosition(755, 385);
	kwad1.setFillColor(Color::Black);
	overlay.setFillColor(Color::White);
	overlay.setOutlineColor(Color::Black);
	overlay.setOutlineThickness(5);
	overlay.setPosition((window.getSize().x / 2) - 300, (window.getSize().y / 2) - 200);
	Text text("          USTAWIENIA:\n\n      Hypermode:", font, 35);
	text.setFillColor(Color::Black);
	text.setPosition((window.getSize().x / 2) - 190, (window.getSize().y / 2) - 175);
	Vector2i pozycjamysz;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			pozycjamysz = Mouse::getPosition(window);
			if (event.type == Event::MouseButtonReleased)
			{
				if (kwad1.getGlobalBounds().contains(static_cast<Vector2f>(pozycjamysz)))
				{
					if (tryb == true) tryb = false;
					else if (tryb == false) tryb = true;
				}
			}
			if (tryb == false)
			{
				kwad2.setFillColor(Color::Black);
			}
			else kwad2.setFillColor(Color::White);
			window.clear(Color::White);
			window.draw(overlay);
			window.draw(text);
			window.draw(kwad1);
			window.draw(kwad2);
			window.display();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) break;
	}
	
}

void menu(RenderWindow& window)
{
	Button Nowagra(Vector2f(window.getSize().x/2 - 100, window.getSize().y / 2 - 150), "NOWA GRA");
	Button Kontynuuj(Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 50), "KONTYNUUJ");
	Button Ustawienie(Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 50), "USTAWIENIA");
	Button Wyjdz(Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 150), "WYJDZ");
	Text tytul("VECTORSPEED", font, 100);
	tytul.setPosition(310,150);
	tytul.setFillColor(Color::Black);
	bool wczyt;
	bool tryb=false;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (Nowagra.myszka_nad(window))
				{
					wczyt = false;
					gra(window,wczyt,tryb);
				}
				else if (Kontynuuj.myszka_nad(window))
				{
					wczyt = true;
					gra(window,wczyt,tryb);
				}
				else if (Ustawienie.myszka_nad(window))
				{
					Ustawienia(window,tryb);
				}
				else if (Wyjdz.myszka_nad(window))
				{
					window.close();
				}
			}
		}

		Nowagra.zmienkolor(window);
		Kontynuuj.zmienkolor(window);
		Ustawienie.zmienkolor(window);
		Wyjdz.zmienkolor(window);

		window.clear(Color::White);
		window.draw(Nowagra.getkwad());
		window.draw(Nowagra.gettekst());

		window.draw(Kontynuuj.getkwad());
		window.draw(Kontynuuj.gettekst());

		window.draw(Ustawienie.getkwad());
		window.draw(Ustawienie.gettekst());

		window.draw(Wyjdz.getkwad());
		window.draw(Wyjdz.gettekst());

		window.draw(tytul);

		window.display();
	}
}

int main()
{
	RenderWindow window(VideoMode(1300, 950), "VectorSpeed");
	if (!font.loadFromFile("AlienRavager.ttf")) 
	{
		cout << "Nie znaleziono pliku czcionki!" << endl;
		return -1;
	}
	menu(window);
	return 0;
}
