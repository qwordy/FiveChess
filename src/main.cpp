#include <stdio.h>
#include "chess.h"

Chess_Window mywin(200, 50, 800, 600, "Chess - Five in a Row");
Chess chess;

int main(int argc, char **argv)
{
	mywin.show(argc, argv);
	return Fl::run();
}
