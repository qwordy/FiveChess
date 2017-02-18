#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

const int shift = 4;

class My_Button : public Fl_Box
{
public:
	My_Button(int x, int y, int w, int h, const char *l = 0);
	void callback(Fl_Callback *callback) {cb = callback;}
	void up() {resize(x(), yy - shift, w(), hh + shift); parent()->redraw();}
	void down() {resize(x(), yy, w(), hh); parent()->redraw();}
	void activate() {living = true;}
	void deactivate() {living = false;}
	int handle(int e);
private:
	Fl_Callback *cb;
	bool living;
	int yy, hh;
};
