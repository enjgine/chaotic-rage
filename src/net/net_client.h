// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <SDL.h>
#include <SDL_net.h>
#include <list>
#include "../rage.h"
#include "net.h"

using namespace std;


class UIUpdate;


class NetClient {
	friend class NetClientSeqPred;

	private:
		GameState * st;
		IPaddress ipaddress;
		Uint16 code;
		UDPsocket sock;
		list<NetMsg> messages;    // queue of messages to go out
		SeqNum seq;               // TODO: is this big enough?
		unsigned int last_ack;    // the time we last got a seq from the server
		NetGameinfo *gameinfo;    // Map, etc, provided at join time
		bool ingame;              // We are in the game

		NetClientSeqPred * seq_pred;

	public:
		NetClient(GameState * st);
		~NetClient();

	private:
		NetClient(const NetClient& disabledCopyConstuctor);

	public:
		void update();

	public:
		/**
		* Start the game join dance
		**/
		NetGameinfo* attemptJoinGame(string address, int port, UIUpdate *ui);

		/**
		* Download the game state
		**/
		bool downloadGameState();

		/**
		* Called before the game
		**/
		void preGame();

		/**
		* Handle errors
		**/
		void error(string msg);

	public:
		// One method for each outgoing network message the client sends out
		void addmsgInfoReq();
		void addmsgJoinReq();
		void addmsgJoinAck();
		void addmsgDataCompl();
		void addmsgChat();
		void addmsgQuit();
		void addmsgKeyMouseStatus(int x, int y, int delta, Uint16 k);

	public:
		// One method for each incoming network message from the server
		unsigned int handleInfoResp(Uint8 *data, unsigned int size);
		unsigned int handleJoinAcc(Uint8 *data, unsigned int size);
		unsigned int handleJoinRej(Uint8 *data, unsigned int size);
		unsigned int handleDataCompl(Uint8 *data, unsigned int size);
		unsigned int handleChat(Uint8 *data, unsigned int size);
		unsigned int handlePlayerDrop(Uint8 *data, unsigned int size);
		unsigned int handleHUD(Uint8 *data, unsigned int size);

		unsigned int handleUnitState(Uint8 *data, unsigned int size);
		unsigned int handleWallState(Uint8 *data, unsigned int size);
		unsigned int handleObjectState(Uint8 *data, unsigned int size);
		unsigned int handleVehicleState(Uint8 *data, unsigned int size);
		unsigned int handleAmmoroundState(Uint8 *data, unsigned int size);
		unsigned int handlePickupState(Uint8 *data, unsigned int size);
		unsigned int handleEntityRem(Uint8 *data, unsigned int size);

	private:
		void bind(string address, int port);
};

class NetClientSeqPred
{
	public:
		NetClient *client;
		bool operator() (const NetMsg& value) { return (this->client->seq > value.seq); }
		NetClientSeqPred(NetClient *c) { this->client = c; }
};
