#pragma once
#include <iostream>
#include <SDL.h>
#include "rage.h"

using namespace std;


class GameState
{
	friend void render(GameState *st, SDL_Surface *screen);
	
	protected:
		vector<Entity*> entities;
		vector<Entity*> entities_add;
		//vector<Unit*> units;
		vector<Particle*> particles;
		//vector<ParticleGenerator*> particlegenerators;
		
	public:
		Player* curr_player;
		Map* map;
		unsigned int anim_frame;
		unsigned int game_time;
		HUD* hud;
		
	public:
		GameState();
		~GameState();
		
	public:
		void addUnit(Unit* unit);
		void addParticle(Particle* particle);
		void addParticleGenerator(ParticleGenerator* generator);
		
		vector<Particle*> * particlesInside(int x, int y, int w, int h);
		
	public:
		void update(int delta);
};
