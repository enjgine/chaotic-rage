// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#include <iostream>
#include <SDL.h>
#include <math.h>
#include "rage.h"

using namespace std;


NPC::NPC(UnitType *uc, GameState *st) : Unit(uc, st)
{
	vals[0] = vals[1] = vals[2] = vals[3] = 0;
	
	this->setState(UNIT_STATE_RUNNING);
}

NPC::~NPC()
{
}


void NPC::hasBeenHit(CollideBox * ours, CollideBox * theirs)
{
	Unit::hasBeenHit(ours, theirs);
	
	// This should be moved into a function in the GameLogic class
	/*if (theirs->e->klass() == UNIT) {
		this->beginFiring();
		currently_hit = true;
	}*/
	// End of stuff to move
}


/**
* Try to find a player and attack them
**/
void NPC::update(int delta)
{
	UnitTypeSettings *ucs = this->uc->getSettings(0);
	
	
	/*if (currently_hit) {
		this->endFiring();
	}
	currently_hit = false;*/
	
	
	// This should be moved into a function in the GameLogic class
	if (st->local_players[0] == NULL) return;
	
	if (st->game_time - vals[0] > 2500) {
		vals[0] = st->game_time;
		vals[1] = getAngleBetweenPoints((int)round(this->x), (int)round(this->y), (int)round(this->st->local_players[0]->x), (int)round(this->st->local_players[0]->y));
		vals[1] = getRandom(vals[1] - 50, vals[1] + 50);
		
		this->desired_angle_aim = getRandom(vals[1] - 50, vals[1] + 50);
		
		//if (firing) {
		//	this->endFiring();
		//} else {
		//	this->beginFiring();
		//}

		if (getRandom(1,8) == 1) {
			this->st->audio->playSound(this->st->getDefaultMod()->getSound("zombie_1"), false);
		}
	}
	
	
	this->desired_angle_aim = clampAngle(this->desired_angle_aim);
	int turn_aim = ppsDeltai(ucs->turn_aim, delta);
	this->angle_aim = angleFromDesired(this->angle_aim, this->desired_angle_aim, turn_aim);
	
	this->desired_angle_move = getRandom(vals[1] - 10, vals[1] + 10);
	
	this->speed += ppsDeltaf(ucs->accel, delta);
	// End of stuff to move
	
	
	Unit::update(delta, ucs);
	
	delete ucs;
}

int NPC::takeDamage(int damage)
{
	int result = Unit::takeDamage(damage);
	
	if (result == 1) {
		this->st->logic->raise_npcdied();
	}
	
	return result;
}
