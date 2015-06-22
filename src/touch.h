// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once

class GameState;


/**
* A finger has touched onto the device
**/
void fingerDown(GameState *st, float x, float y);

/**
* A finger has moved
**/
void fingerMove(GameState *st, int finger, float x, float y);

/**
* Multiple finger gesture event
**/
void multigesture(GameState *st, unsigned int fingers, float x, float y);

/**
* A finger has raised off the device
**/
void fingerUp(GameState *st);
