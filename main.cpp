#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
using namespace sf;

float offsetX = 0, offsetY = 0;

const int H = 17;
const int W = 150;

String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                            w                                       0",
"0    w                                                                               w                                                               0",
"0                   w                                  w                   w                                                                 w       0",
"0                                      w                                                                               w                             0",
"0                                                                                                         w                                          0",
"0                      c                      kk kk                           k    k    k kkk kkkkk                                                  0",
"0                                            kkkkkkk                    r     k k k k   k k  k  k                                                    0",
"0                                             kkkkk                    rr     k  k   k  k k k   k                           w                  w     0",
"0                                               k                     rrr     k       k k k     k                                                    0",
"0      w        c    kckck                                           rrrr                                w                                    r     0",
"0                                      t0                           rrrrr                                   t0                               rrrr    0",
"0G                                     00              t0          rrrrrr            G                      00    w       t0                rrrrrrr  0",
"0           d    g       d             00              00         rrrrrrr                                   00            00               rrrrrrrrrr0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};


class PLAYER {
public:
	float dx, dy;
	FloatRect rect;
	bool onGround = true;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture& image) {
		sprite.setTexture(image);
		rect = FloatRect(100, 180, 16, 16);

		dx = 0.1;
		dy = 0.1;
		currentFrame = 0;
	}

	void update(float time) {

		rect.left += dx * time;

		Collision(0);

		if (onGround == false) { dy = dy + 0.0002 * time; }
		rect.top += dy * time;
		onGround = false;
		Collision(1);

		currentFrame += 0.005 * time;
		if (currentFrame > 3) { currentFrame -= 3; }

		if (dx > 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
		if (dx < 0) sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	void Collision(int num)
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
				{
					if (dy > 0 && num == 1)
					{
						rect.top = i * 16 - rect.height;
						dy = 0;
						onGround = true;
					}
					if (dy < 0 && num == 1) {
						rect.top = i * 16 + 16;
						dy = 0;
					}
					if (dx > 0 && num == 0)
					{
						rect.left = j * 16 - rect.width;
					}
					if (dx < 0 && num == 0)
					{
						rect.left = j * 16 + 16;
					}
				}

				if (TileMap[i][j] == 'c') {
					// TileMap[i][j]=' '; 
				}
			}

	}

};

class ENEMY {
public:
	float dx, dy;
	FloatRect rect;
	bool life;
	Sprite sprite;
	float currentFrame;

	void set(Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);

		dx = 0.05;
		currentFrame = 0;
		life = true;
	}

	void update(float time) {

		rect.left += dx * time;

		Collision();

		currentFrame += 0.005 * time;
		if (currentFrame > 2) { currentFrame -= 2; }

		sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
		if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	}

	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0'))
				{
					if (dx > 0) {
						rect.left = j * 16 - rect.width;
						dx *= -1;
					}
					else if (dx < 0) {
						rect.left = j * 16 + 16;
						dx *= -1;
					}
				}

			}

	}

};

int main()
{
	RenderWindow window(VideoMode(400, 250), "SFML works!");

	Texture tileSet;
	tileSet.loadFromFile("Mario_tileset.png");

	float currentFrame = 0;
	Sprite tile(tileSet);

	PLAYER p(tileSet);
	p.sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
	ENEMY e;
	e.set(tileSet, 48 * 16, 13 * 16);

	SoundBuffer buffer;
	buffer.loadFromFile("jump.ogg");
	Sound sound(buffer);
	Music music;
	music.openFromFile("theme.ogg");
	music.play();

	Font font;
	font.loadFromFile("sansation.ttf");

	Text mytext("Hello!", font, 50);

	mytext.setFillColor(Color::Red);
	mytext.setPosition(10, 10);

	float q = 1;

	RectangleShape rectangle(Vector2f(32, 32));

	Texture menu_texture1, menu_texture2, menu_texture3, about_texture;
	menu_texture1.loadFromFile("111.png");
	menu_texture2.loadFromFile("333.png");
	menu_texture3.loadFromFile("222.png");
	about_texture.loadFromFile("about.png");
	Sprite menu1(menu_texture1), menu2(menu_texture2), menu3(menu_texture3), about(about_texture);
	bool Menu = 1;
	int MenuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	if (!menu_texture1.loadFromFile("111.png"))
	{
		std::cout << "Error loading 111.png!" << std::endl;
	}
	if (!music.openFromFile("theme.ogg")) {
		std::cerr << "Error: Could not load theme.ogg!" << std::endl;
	}
	else {
		music.play();
	}
	while (Menu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		MenuNum = 0;

		// Обработка событий в меню
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				Menu = false;
			}
		}

		window.clear(Color(0, 0, 0));

		// Проверка hover и клика
		Vector2i mousePos = Mouse::getPosition(window);
		if (IntRect(100, 30, 200, 50).contains(mousePos)) { menu1.setColor(Color::Yellow); MenuNum = 1; }
		if (IntRect(100, 90, 200, 50).contains(mousePos)) { menu2.setColor(Color::Yellow); MenuNum = 2; }
		if (IntRect(100, 150, 200, 50).contains(mousePos)) { menu3.setColor(Color::Yellow); MenuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (MenuNum == 1) Menu = false;
			if (MenuNum == 2)
			{
				window.draw(about);
				window.display();
				while (!Keyboard::isKeyPressed(Keyboard::Escape) && window.isOpen())
				{
					Event aboutEvent;
					while (window.pollEvent(aboutEvent))
					{
						if (aboutEvent.type == Event::Closed)
						{
							window.close();
							Menu = false;
						}
					}
				}
			}
			if (MenuNum == 3)
			{
				window.close();
				Menu = false;
			}
		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.display();
	}

	Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dx = -0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dx = +0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (p.onGround) { p.dy = -0.15; p.onGround = false; sound.play(); }
		}

		p.update(time);
		e.update(time);
		if (p.rect.intersects(e.rect))
		{
			if (e.life) {
				if (p.dy > 0) { e.dx = 0; p.dy = -0.2; e.life = false; }
				else { p.sprite.setColor(Color::Red); if (q > 0) { q--; } }
			}
		}


		if (p.rect.left > 300) { offsetX = p.rect.left - 600 / 2; }
		if (p.rect.top > 200) { offsetY = p.rect.top - 400 / 2; }

		window.clear(Color::White);

		window.clear(Color(107, 140, 255));

		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

				if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(143, 112, 16, 16));

				if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

				if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

				if (TileMap[i][j] == 'g')  tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

				if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

				if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));

				if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

				if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

				if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

				tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
				window.draw(tile);
			}
		std::ostringstream ss;
		ss << q;
		mytext.setString(ss.str());
		window.draw(mytext);

		window.draw(p.sprite);
		window.draw(e.sprite);
		window.display();
	}
	return 0;
}