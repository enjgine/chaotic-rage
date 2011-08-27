// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#include <iostream>
#include <SDL.h>
#include <confuse.h>
#include <zzip/zzip.h>
#include "rage.h"

using namespace std;


/**
* Config file opts
**/
// Damage
static cfg_opt_t damage_opts[] =
{
	CFG_INT((char*) "health", 0, CFGF_NONE),
	CFG_STR((char*) "model", (char*)"", CFGF_NONE),
	CFG_END()
};

// Walltype section
cfg_opt_t objecttype_opts[] =
{
	CFG_STR((char*) "name", (char*)"", CFGF_NONE),
	CFG_STR((char*) "model", (char*)"", CFGF_NONE),
	CFG_STR_LIST((char*) "walk_sounds", 0, CFGF_NONE),
	CFG_SEC((char*) "damage", damage_opts, CFGF_MULTI),

	CFG_STR((char*) "add-object", (char*)"", CFGF_NONE),
	CFG_STR((char*) "show-message", (char*)"", CFGF_NONE),
	CFG_INT((char*) "drive", 0, CFGF_NONE),

	CFG_END()
};


/**
* Item loading function handler
**/
ObjectType* loadItemObjectType(cfg_t* cfg_item, Mod* mod)
{
	ObjectType* wt;
	string filename;
	int size;
	
	wt = new ObjectType();
	wt->name = cfg_getstr(cfg_item, "name");
	wt->check_radius = 30;	//TODO: dynamic
	
	wt->add_object = cfg_getstr(cfg_item, "add-object");
	wt->show_message = cfg_getstr(cfg_item, "show-message");
	wt->drive = cfg_getint(cfg_item, "drive");

	char * tmp = cfg_getstr(cfg_item, "model");
	if (tmp != NULL) wt->model = mod->getAnimModel(tmp);
	
	// Load damage states
	size = cfg_size(cfg_item, "damage");
	if (size == 0) {
		ObjectTypeDamage * dam = new ObjectTypeDamage();
		dam->health = 0;
		dam->model = mod->getAnimModel("null");
		wt->damage_models.push_back(dam);
		
	} else {
		for (int j = 0; j < size; j++) {
			cfg_t *cfg_damage = cfg_getnsec(cfg_item, "damage", j);
			
			char * tmp = cfg_getstr(cfg_damage, "model");
			if (tmp == NULL) return NULL;
			
			ObjectTypeDamage * dam = new ObjectTypeDamage();
			
			dam->health = cfg_getint(cfg_damage, "health");
			dam->model = mod->getAnimModel(tmp);
			
			wt->damage_models.push_back(dam);
		}
	}
	
	return wt;
}


ObjectType::ObjectType()
{
	this->surf = NULL;
	this->ground_type = NULL;
}
