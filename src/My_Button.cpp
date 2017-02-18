#include "My_Button.h"

My_Button::My_Button(int x, int y, int w, int h, const char *l) : Fl_Box(x, y, w, h, l), yy(y), hh(h)
{
	living = true;
	align(FL_ALIGN_IMAGE_BACKDROP);
}

int My_Button::handle(int e)
{
	if (!living) return 0;
	switch(e)
	{
	case FL_PUSH:
		down();
		cb(this, 0);
		return 1;
	case FL_RELEASE:
		up();
		return 1;
	case FL_ENTER:
		up();
		return 1;
	case FL_LEAVE:
		down();
		return 1;
	}
	return 0;
}