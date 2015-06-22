// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <SDL.h>
#include <SDL_net.h>
#include "../rage.h"
#include "net.h"

using namespace std;


// How far behind a client can be before being dropped
#define MAX_SEQ_LAG 20

class ServerConfig;


class NetServer {
	friend class NetServerSeqPred;

	private:
		GameState * st;
		ServerConfig * conf;
		IPaddress ipaddress;
		UDPsocket sock;
		list<NetMsg> messages;		// TODO: re-architecture to involve less allocs and copies. Ringbuffer? Swapbuffer?
		SeqNum seq;
		vector<NetServerClientInfo*> clients;

		NetServerSeqPred * seq_pred;

	public:
		NetServer(GameState * st, ServerConfig * conf);
		~NetServer();

	private:
		NetServer(const NetServer & disabledCopyConstuctor);

		/**
		* Drop a client
		**/
		void dropClient(NetServerClientInfo *client);

		/**
		* Handle errors
		**/
		void error(string msg);

	public:
		/**
		* Called every frame to update stuff
		**/
		bool update();

		/**
		* Set up listening on the network
		**/
		void listen();

		// One method for each outgoing network message the server sends out
		void addmsgInfoResp();
		void addmsgJoinAcc(NetServerClientInfo *client);
		void addmsgJoinRej();
		void addmsgDataCompl();
		void addmsgChat();
		void addmsgHUD(HUDLabel *l);
		void addmsgClientDrop(NetServerClientInfo *client);
		void addmsgUnitState(Unit *u);
		void addmsgWallState(Wall *w);
		void addmsgObjectState(Object *o);
		void addmsgVehicleState(Vehicle *v);
		void addmsgAmmoRoundState(AmmoRound *ar);
		void addmsgPickupState(Pickup *p);
		void addmsgEntityRem(Entity *e);

		// One method for each incoming network message from the client
		unsigned int handleInfoReq(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleJoinReq(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleJoinAck(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleJoinDone(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleChat(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleQuit(NetServerClientInfo *client, Uint8 *data, unsigned int size);
		unsigned int handleKeyMouseStatus(NetServerClientInfo *client, Uint8 *data, unsigned int size);
};


/**
* Client info (ip, code) -> (seq, slot)
**/
class NetServerClientInfo
{
	public:
		IPaddress ipaddress;
		Uint16 code;

	public:
		SeqNum seq;		// TODO: again...big enough?
		unsigned int slot;
		bool inlist;
		bool ingame;
		bool del;

		NetServerClientInfo() { seq = 0; slot = 0; del = false; inlist = false; ingame = false; }
};


/**
* Used to determine messages that should be removed
**/
class NetServerSeqPred
{
	public:
		NetServer *server;

		// Remove any messages with a seq lower than the lowest client
		bool operator() (const NetMsg& value) {
			SeqNum lowest = server->seq;
			for (vector<NetServerClientInfo*>::iterator cli = server->clients.begin(); cli != server->clients.end(); ++cli) {
				if ((*cli) == NULL) continue;
				if ((*cli)->seq < lowest) lowest = (*cli)->seq;
			}
			return (lowest > value.seq);
		}

		NetServerSeqPred(NetServer *s) { this->server = s; }
};
