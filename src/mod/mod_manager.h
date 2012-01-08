// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <iostream>
#include <SDL.h>
#include "../rage.h"

using namespace std;


class ModManager {
	private:
		vector<Mod*> mods;
		GameState * st;
		
	public:
		ModManager(GameState * st);
		
	public:	
		void addMod(Mod * mod);
		Mod * getMod(string name);
		Mod * getDefaultMod();

		bool reloadAttrs();

		AnimModel * getAnimModel(int id);
		FloorType * getFloorType(int id);
		GameType * getGameType(int id);
		ObjectType * getObjectType(int id);
		ParticleType * getParticleType(int id);
		ParticleGenType * getParticleGenType(int id);
		Song * getSong(int id);
		Sound * getSound(int id);
		UnitType * getUnitType(int id);
		WallType * getWallType(int id);
		WeaponType * getWeaponType(int id);
		
		AnimModel * getAnimModel(string name);
		FloorType * getFloorType(string name);
		GameType * getGameType(string name);
		ObjectType * getObjectType(string name);
		ParticleType * getParticleType(string name);
		ParticleGenType * getParticleGenType(string name);
		UnitType * getUnitType(string name);
		Song * getSong(string name);
		Sound * getSound(string name);
		WallType * getWallType(string name);
		WeaponType * getWeaponType(string name);
		
		void addObjectType(ObjectType * ot);
		
		Song * getRandomSong();

		void getAllGameTypes(vector<GameType*>::iterator * start, vector<GameType*>::iterator * end);
		void getAllUnitTypes(vector<UnitType*>::iterator * start, vector<UnitType*>::iterator * end);
};