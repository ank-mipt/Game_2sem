#include "update.h"
 void update(float time){

 	rect.left += dx * time;

	Collision(0);

	if(onGround == false){dy = dy + 0.0002 * time;}
	rect.top += dy*time;
	onGround = false;
	Collision(1);

	currentFrame +=0.005 * time;
	if(currentFrame > 3){currentFrame-=3;}

	if (dx>0) sprite.setTextureRect(IntRect(112+31*int(currentFrame),144,16,16));
	if (dx<0) sprite.setTextureRect(IntRect(112+31*int(currentFrame)+16,144,-16,16));

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	dx = 0;
}
