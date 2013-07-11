// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#include <iostream>
#include "../rage.h"
#include "../gamestate.h"
#include "../map.h"
#include "render_debug.h"
#include <SDL_image.h>


using namespace std;


RenderDebug::RenderDebug(GameState * st) : Render(st)
{
	this->sprite_wall = SDL_LoadBMP("data/debug/wall.bmp");
	this->sprite_vehicle = SDL_LoadBMP("data/debug/vehicle.bmp");
	this->sprite_object = SDL_LoadBMP("data/debug/object.bmp");
	this->sprite_unit = SDL_LoadBMP("data/debug/unit.bmp");
	this->sprite_player = SDL_LoadBMP("data/debug/player.bmp");
}

RenderDebug::~RenderDebug()
{
	SDL_FreeSurface(this->sprite_wall);
	SDL_FreeSurface(this->sprite_unit);
	SDL_FreeSurface(this->sprite_vehicle);
	SDL_FreeSurface(this->sprite_object);
	SDL_FreeSurface(this->sprite_player);
	SDL_FreeSurface(this->screen);
}


/**
* Sets the screen size
**/
void RenderDebug::setScreenSize(int width, int height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	
	this->screen = SDL_SetVideoMode(width, height, 32, 0);
	if (screen == NULL) {
		fprintf(stderr, "Unable to set %ix%i video: %s\n", width, height, SDL_GetError());
		exit(1);
	}
	
	SDL_WM_SetCaption("Chaotic Rage (debug)", "Chaotic Rage (debug)");
	SDL_ShowCursor(SDL_ENABLE);
}


/**
* Internal sprite loading from a SDL_RWops
**/
SpritePtr RenderDebug::int_loadSprite(SDL_RWops *rw, string filename)
{
	SDL_Surface * surf;
	
	surf = IMG_Load_RW(rw, 0);
	if (surf == NULL) {
		fprintf(stderr, "Couldn't load sprite '%s'\n", filename.c_str());
		load_err = true;
		return NULL;
	}

	// Create the sprite object
	SpritePtr sprite = new struct sprite();
	sprite->w = surf->w;
	sprite->h = surf->h;
	sprite->orig = surf;
	
	return sprite;
}


/**
* Renders a sprite.
* Should only be used if the the caller was called by this classes 'Render' function.
**/
void RenderDebug::renderSprite(SpritePtr sprite, int x, int y)
{
}


/**
* Renders a sprite.
* Should only be used if the the caller was called by this classes 'Render' function.
**/
void RenderDebug::renderSprite(SpritePtr sprite, int x, int y, int w, int h)
{
}


/**
* Before the game
**/
void RenderDebug::preGame()
{
}


/**
* After the game
**/
void RenderDebug::postGame()
{
}


/**
* Clears all colour from a given pixel for a given sprite
**/
void RenderDebug::clearPixel(int x, int y)
{
}


/**
* Free sprite memory
**/
void RenderDebug::freeSprite(SpritePtr sprite)
{
	delete(sprite);
}


/**
* Returns sprite width
**/
int RenderDebug::getSpriteWidth(SpritePtr sprite)
{
	return 0;
}

/**
* Returns sprite height
**/
int RenderDebug::getSpriteHeight(SpritePtr sprite)
{
	return 0;
}


/**
* Does a render every ~500ms
**/
void RenderDebug::render()
{
	static int last_render = st->game_time;
	
	if (st->game_time - last_render < 500) return;
	last_render = st->game_time;
	
	
	float scalex = ((float)st->map->width) / ((float)this->width);
	float scaley = ((float)st->map->height) / ((float)this->height);

	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;
	src.w = 16;
	src.h = 16;
	dest.w = 16;
	dest.h = 16;

	SDL_FillRect(screen, NULL, 0);
	
	// Entities
	for (list<Entity*>::iterator it = st->entities.begin(); it != st->entities.end(); it++) {
		Entity *e = (*it);
		
		btTransform trans = e->getTransform();
		
		dest.x = (trans.getOrigin().getX() / scalex) - 8;
		dest.y = (trans.getOrigin().getZ() / scaley) - 8;
		
		if (e->klass() == WALL) {
			SDL_BlitSurface(this->sprite_wall, &src, screen, &dest);
			
		} else if (e->klass() == VEHICLE) {
			SDL_BlitSurface(this->sprite_vehicle, &src, screen, &dest);
			
		} else if (e->klass() == OBJECT) {
			SDL_BlitSurface(this->sprite_object, &src, screen, &dest);
			
		} else if (e->klass() == UNIT) {
			if (((Unit*)e)->slot == 0) {
				SDL_BlitSurface(this->sprite_unit, &src, screen, &dest);
			} else {
				SDL_BlitSurface(this->sprite_player, &src, screen, &dest);
			}
		}
	}
	
	SDL_Flip(screen);
	
	SDL_WM_GrabInput(SDL_GRAB_OFF);
	SDL_ShowCursor(SDL_ENABLE);
	st->reset_mouse = false;
}


