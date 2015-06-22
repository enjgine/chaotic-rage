// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include "entity.h"

class AnimPlay;
class GameState;
class WallType;


class Wall : public Entity
{
	public:
		virtual EntityClass klass() const { return WALL; }

	public:
		WallType* wt;
		float health;

	protected:
		AnimPlay * anim;

	public:
		Wall(WallType *pt, GameState *st, float x, float y, float z, float angle);
		virtual ~Wall();

	public:
		virtual void update(int delta);
		virtual void takeDamage(float damage);
};
