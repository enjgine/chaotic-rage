// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#include <iostream>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "../util/quadratic.h"
#include "../rage.h"
#include "../gamestate.h"
#include "../physics_bullet.h"
#include "ghost_objects.h"

using namespace std;




/**
* Create a chost object for collision detection
**/
btGhostObject* create_ghost(btTransform& xform, float radius)
{
	btGhostObject* ghost = new btGhostObject();

	ghost->setWorldTransform(xform);
	ghost->setCollisionFlags(ghost->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	btSphereShape* shape = new btSphereShape(radius);
	ghost->setCollisionShape(shape);

	return ghost;
}


/**
* If there is anything within the ghost radius, apply damage as appropriate
**/
void apply_ghost_damage(btGhostObject* ghost, Quadratic damage, float radius)
{
	float dist;
	
	const btAlignedObjectArray <btCollisionObject*>* pObjsInsideGhostObject;
	pObjsInsideGhostObject = &ghost->getOverlappingPairs();
	
	for (int i = 0; i < pObjsInsideGhostObject->size(); ++i) {
		btCollisionObject* co = pObjsInsideGhostObject->at(i);
		
		Entity* e = (Entity*) co->getUserPointer();
		if (e == NULL) continue;
		if (e->klass() != UNIT) continue;
		
		// Determine distance
		dist = ghost->getWorldTransform().getOrigin().distance(co->getWorldTransform().getOrigin());
		if (dist >= radius) continue;
		
		// We solve the Quadratic based on the distance from the OUTSIDE of the ghost
		((Unit*)e)->takeDamage(damage.solve(radius - dist));
	}
}


/**
* If there is any units within the ghost radius?
* TODO: Friendly fire?
**/
bool check_ghost_triggered_units(btGhostObject* ghost)
{
	const btAlignedObjectArray <btCollisionObject*>* pObjsInsideGhostObject;
	pObjsInsideGhostObject = &ghost->getOverlappingPairs();
	
	for (int i = 0; i < pObjsInsideGhostObject->size(); ++i) {
		btCollisionObject* co = pObjsInsideGhostObject->at(i);
		
		Entity* e = (Entity*) co->getUserPointer();
		if (e == NULL) continue;
		
		if (e->klass() == UNIT) {
			return true;
		}
	}

	return false;
}


/**
* If there is anything within the ghost radius?
**/
bool check_ghost_triggered_any(btGhostObject* ghost)
{
	const btAlignedObjectArray <btCollisionObject*>* pObjsInsideGhostObject;
	pObjsInsideGhostObject = &ghost->getOverlappingPairs();
	
	for (int i = 0; i < pObjsInsideGhostObject->size(); ++i) {
		btCollisionObject* co = pObjsInsideGhostObject->at(i);
		cout << "hit: " << co << endl;	
	}
	
	return (pObjsInsideGhostObject->size() > 0);
}


