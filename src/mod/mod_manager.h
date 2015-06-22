// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include "../rage.h"

using namespace std;


class Mod;
class GameState;
class AIType;
class Campaign;
class GameType;
class ObjectType;
class PickupType;
class Song;
class UnitType;
class VehicleType;
class WallType;
class WeaponType;
class AssimpModel;


class ModManager {
	private:
		vector<Mod*> * mods;
		Mod* base;
		Mod* suppl;

	public:
		ModManager();
		~ModManager();

	private:
		ModManager(const ModManager& disabledCopyConstuctor);

	public:
		void addMod(Mod *mod);
		void remMod(Mod *mod);
		void setBase(Mod *mod) { this->base = mod; }
		void setSuppl(Mod *mod) { this->suppl = mod; }
		Mod * getDefaultMod() { return this->base; }
		Mod * getBase() { return this->base; }
		Mod * getSuppl() { return this->suppl; }
		Mod * getSupplOrBase();
		Mod * getMod(string name);
		vector<string> * getLoadedMods();
		vector<string> * getAvailMods();

		bool reloadAttrs();

		AIType * getAIType(CRC32 id);
		ObjectType * getObjectType(CRC32 id);
		PickupType * getPickupType(CRC32 id);
		UnitType * getUnitType(CRC32 id);
		VehicleType * getVehicleType(CRC32 id);
		WallType * getWallType(CRC32 id);
		WeaponType * getWeaponType(CRC32 id);

		AIType * getAIType(string name);
		GameType * getGameType(string name);
		ObjectType * getObjectType(string name);
		PickupType * getPickupType(string name);
		Song * getSong(string name);
		UnitType * getUnitType(string name);
		VehicleType * getVehicleType(string name);
		WallType * getWallType(string name);
		WeaponType * getWeaponType(string name);

		Song * getRandomSong();

		vector<GameType*> * getAllGameTypes();
		vector<UnitType*> * getAllUnitTypes();
		vector<WeaponType*> * getAllWeaponTypes();
};


bool loadMods(GameState *st, UIUpdate* ui);



