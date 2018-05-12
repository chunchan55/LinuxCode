#ifndef _WINDOW_H_
#define _WINDOW_H_

#include<iostream>
#include<string>
#include"ncurses"
class window
{
	public:
		window();
		~window();
		void drawHeader();
	    void drawOutput();
		void drawFlist();
		void drawInput();
		void putstrtowin(WINDOW*WIN,int y,int x,std::string&str);
		void getstrfromwin(WINDOW*win,std::string&str);
	//protected:
	public:
		WINDOW* header;
		WINDOW* output;
     	WINDOW* flist;
		WINDOW* input;
};
