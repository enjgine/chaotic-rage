// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include "entity.h"

class AnimPlay;
class GameState;
class PickupType;
class Unit;


class Pickup : public Entity
{
	public:
		virtual EntityClass klass() const { return PICKUP; }

	protected:
		PickupType* pt;
		AnimPlay * anim;

	public:
		Pickup(PickupType *pt, GameState *st, float x, float z);
		Pickup(PickupType *pt, GameState *st, float x, float y, float z);
		virtual ~Pickup();

		/**
		* Called by the unit when it interacts with a pickup
		* Return true on success and false on failure (e.g. wrong weapon for ammo box)
		**/
		bool doUse(Unit *u);

		/**
		* Get the pickup type
		**/
		PickupType* getPickupType() { return this->pt; }


	public:
		virtual void update(int delta);
};
