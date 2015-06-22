// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include "entity.h"

class AnimPlay;
class GameState;
class btCollisionShape;
class btTransform;

using namespace std;


class btTransform;
class btCollisionShape;

class Decaying : public Entity
{
	public:
		virtual EntityClass klass() const { return NONE; }

	public:
		AnimPlay *anim;
		unsigned int remove_after;

	private:
		static btCollisionShape* col_shape;

	public:
		Decaying(GameState *st, const btTransform &xform, AnimPlay *model, float mass = 0.0f);
		virtual ~Decaying();

		virtual void update(int delta);
};
