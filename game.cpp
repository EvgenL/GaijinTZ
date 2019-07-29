#include "stdafx.h"
#include "stdlib.h"
#include "svga/svga.h"
#include <winuser.h>
#include <cstdint>
#include <iostream>

#include "time.h"
#include "graphics.h"
#include "Block.h"
#include "Ball.h"
#include <vector>


const int BLOCKS_N = 40;


unsigned block_x_size = 40;
unsigned block_y_size = 100;

const float PLATFORM_SPEED = 7.0f;

const float ball_vel_magnitude = 0.5f;

Block all_blocks[BLOCKS_N];
std::vector<Ball*> all_balls;
int balls_N = 0;
Platform platform;



//This function update full screen from scrptr. The array should be at least sv_height*scrpitch bytes size;
void w32_update_screen(void *scrptr,unsigned scrpitch);

//If this variable sets to true - game will quit

extern bool game_quited;

// these variables provide access to joystick and joystick buttons
// In this version joystick is simulated on Arrows and Z X buttons

// [0]-X axis (-501 - left; 501 - right)
// [1]-Y axis (-501 - left; 501 - right)
extern int gAxis[2];
//0 - not pressed; 1 - pressed
extern int gButtons[6];

//sv_width and sv_height variables are width and height of screen
extern unsigned int sv_width,sv_height;

//These functions called from another thread, when a button is pressed or released
void win32_key_down(unsigned k){
  if(k==VK_F1) game_quited=true;
}
void win32_key_up(unsigned){}

//This is default fullscreen shadow buffer. You can use it if you want to.
static unsigned *shadow_buf=NULL;

void spawn_blocks()
{
	srand(time(NULL));

	int span = 20;

	int x_pos = 0;
	int y_pos = span * 2;

	int j = 0;

	for (int i = 0; i < BLOCKS_N; i++)
	{
		x_pos += span;
		
		Block *b = new Block();

		b->pos_x = x_pos;
		b->pos_y = y_pos;
		
		x_pos += b->size_x;

		all_blocks[i] = *b;

		if (x_pos + span + b->size_x > sv_width)
		{
			x_pos = 0;
			y_pos += span + b->size_y;
		}
	}
}

void spawn_ball(unsigned x, unsigned y, float v_x, float v_y)
{
	balls_N++;
	

	Ball *b = new Ball(x, y, v_x, v_y);

	all_balls.push_back(b);
	
}

void spawn_ball()
{
	spawn_ball(sv_width / 2, sv_height / 2, -200.0f, -200.0f);
}

void spawn_platform()
{
	Platform p = *new Platform();

	p.pos_x = sv_width / 2.0f - p.size_x / 2.0f;
	p.pos_y = sv_height - p.size_y * 2.0f;

	platform = p;
}

void init_game(){
  shadow_buf=new unsigned [sv_width*sv_height];
  memset(all_blocks, 0, BLOCKS_N);

  spawn_blocks();

  spawn_ball();

  spawn_platform();
}

void close_game(){
  if(shadow_buf) delete shadow_buf;
  shadow_buf=NULL;
}

//draw the game to screen
void draw_game() {
	if (!shadow_buf)return;
	memset(shadow_buf, 0, sv_width*sv_height * 4);



	//here you should draw anything you want in to shadow buffer. (0 0) is left top corner

	// draw blocks
	for (int i = 0; i < BLOCKS_N; i++)
	{
		Block b = all_blocks[i];

		if (b.broken) continue;

		draw_rectangle(shadow_buf, sv_width, sv_height, 
			b.pos_x, b.pos_y, b.size_x, b.size_y, b.color);

	}
	// draw balls
	for (int i = 0; i < all_balls.size(); i++)
	{
		Ball *b = all_balls.at(i);

		draw_rectangle(shadow_buf, sv_width, sv_height,
			b->pos_x, b->pos_y, b->size_x, b->size_y, b->color);
	}
	// draw platform
	draw_rectangle(shadow_buf, sv_width, sv_height,
		platform.pos_x, platform.pos_y, platform.size_x, platform.size_y, platform.color);

	w32_update_screen(shadow_buf, sv_width * 4);
}



//act the game. dt - is time passed from previous act
void act_game(float dt){


	// update balls
	for (int i = 0; i < all_balls.size(); i++)
	{
		Ball *b = all_balls.at(i);

		b->move(dt);
		b->check_collisions(all_blocks, BLOCKS_N, platform, sv_width, sv_height);


	}

	// check input
	if (gAxis[0] != 0)
	{
		platform.move(gAxis[0] * dt * PLATFORM_SPEED);
	}
}
