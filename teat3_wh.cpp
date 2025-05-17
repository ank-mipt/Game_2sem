#include "update.h"
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

		PLAYER(Texture &image){
			sprite.setTexture(image);
			rect = FloatRect(100,180,16,16);

			dx = 0.1;
			dy = 0.1;
			currentFrame = 0;
 	}


void Collision(int num)
{
	
	for (int i = rect.top/16 ; i<(rect.top + rect.height)/16; i++)
		for (int j = rect.left/16; j<(rect.left + rect.width)/16; j++)
			 {
				 if ((TileMap[i][j]=='P') || (TileMap[i][j]=='k') || (TileMap[i][j]=='0') || (TileMap[i][j]=='r') || (TileMap[i][j]=='t'))
				                         { 
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

				 if (TileMap[i][j]=='c') {
												 // TileMap[i][j]=' '; 
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
	p.sprite.setTextureRect(IntRect(40*int(currentFrame), 244, 40, 50));
 
 	Clock clock;
		
		RectangleShape rectangle(Vector2f(32, 32));

    	while (window.isOpen()){
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
		sf::Event event;
        	while (window.pollEvent(event))
        		{
           			if (event.type == sf::Event::Closed)
                		window.close();
        		}
 
 		if (Keyboard::isKeyPressed(Keyboard::Left)){
  			p.dx = -0.1;
 		}
 		if (Keyboard::isKeyPressed(Keyboard::Right)){
  			p.dx = +0.1;
 		}
 		if (Keyboard::isKeyPressed(Keyboard::Up)){
 			if(p.onGround){p.dy=-0.25; p.onGround = false;}
 		}
 	
 	p.update(time);
	
	if(p.rect.left > 300) {offsetX = p.rect.left - 600/2;}
	if (p.rect.top > 200) {offsetY = p.rect.top - 400/2;}

        window.clear(Color::White);

		window.clear(Color(107,140,255));

		 for (int i=0; i<H; i++)
			 for (int j=0; j<W; j++)
			  { 
				if (TileMap[i][j]=='P')  tile.setTextureRect( IntRect(143-16*3,112,16,16) );

				if (TileMap[i][j]=='k')  tile.setTextureRect( IntRect(143,112,16,16) );
				                                 
   			    if (TileMap[i][j]=='c')  tile.setTextureRect( IntRect(143-16,112,16,16) );

				if (TileMap[i][j]=='t')  tile.setTextureRect( IntRect(0,47,32,95-47) );

				if (TileMap[i][j]=='g')  tile.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) );

				if (TileMap[i][j]=='G')  tile.setTextureRect( IntRect(145,222,222-145,255-222) );

			    if (TileMap[i][j]=='d')  tile.setTextureRect( IntRect(0,106,74,127-106) );

				if (TileMap[i][j]=='w')  tile.setTextureRect( IntRect(99,224,140-99,255-224) );

				if (TileMap[i][j]=='r')  tile.setTextureRect( IntRect(143-32,112,16,16) );

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')) continue;

  			    tile.setPosition(j*16-offsetX,i*16 - offsetY) ; 
		        window.draw(tile);
		     }

        window.draw(p.sprite);
        window.display();
    }
    return 0;
}