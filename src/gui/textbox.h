// This file is part of Chaotic Rage (c) 2010 Josh Heidenreich
//
// kate: tab-width 4; indent-width 4; space-indent off; word-wrap off;

#pragma once
#include <vector>
#include <guichan.hpp>
#include "dialog.h"


using namespace std;

class GameManager;
class GameState;


/**
* Allows the user to enter some text
**/
class DialogTextBox : public Dialog {
	private:
		GameState * st;
		string title;
		gcn::TextBox* text;
		gcn::ScrollArea* scroller;

	public:
		DialogTextBox(GameState* st, string title);
		virtual ~DialogTextBox();

		virtual gcn::Container* setup();
		virtual string getName() { return "textbox"; }

	public:
		/**
		* Get the text of this box
		**/
		string getText() const;

		/**
		* Set the text of this box
		**/
		void setText(string text);

		/**
		* Append a line of text to this box
		**/
		void appendLine(const string &text);
};
