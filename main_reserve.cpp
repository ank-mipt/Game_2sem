#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
using namespace sf;

# include "anim.hpp"
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


int main()
{
	RenderWindow window(VideoMode(400, 250), "SFML works!");

	Texture q;
	q.loadFromFile("fang.png");
	AnimationManager anim;

	anim.create("walk", q, 0, 244, 40, 50, 6, 0.005, 40);
	anim.create("jump", q, 0, 528, 29, 30, 4, 0.0045, 38);
	anim.create("duck", q, 0, 436, 80, 20, 1, 0.005, 43);
	anim.create("stay", q, 0, 187, 42, 52, 3, 0.002, 42);
	anim.create("shoot", q, 0, 572, 45, 52, 5, 0.004, 45);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		if (time > 20) time = 20;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		anim.set("stay");
		if (Keyboard::isKeyPressed(Keyboard::Right)) anim.set("walk");
		if (Keyboard::isKeyPressed(Keyboard::Left)) anim.set("walk");
		if (Keyboard::isKeyPressed(Keyboard::Up)) anim.set("jump");
		if (Keyboard::isKeyPressed(Keyboard::Down)) anim.set("duck");
		if (Keyboard::isKeyPressed(Keyboard::Space)) anim.set("shoot");

		anim.tick(time);

		window.clear(Color(255, 255, 255));
		anim.draw(window, 50, 100);


		window.display();
	}


	return 0;
}