#include <FL/Fl.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include "My_Button.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <vector>

using std::vector;

const int x_begin = 40, y_begin = 40, Gap = 37;

const Fl_Color button_label_color[3] = {152, 255, 255};

typedef enum {Empty, Black, White, Draw} Color;

struct move_t
{
	int i, j;
};

class Square : public Fl_Widget
{
public:
	Square(int x, int y, int a) : Fl_Widget(x, y, a, a, 0), effect_color(FL_BLUE) {}
	void draw();
	Fl_Color effect_color;
};

class Grid : public Fl_Widget
{
public:
	Grid() : Fl_Widget(x_begin-int(Gap/2), y_begin-int(Gap/2), Gap*15, Gap*15, 0) {}
	void draw();
	int handle(int e);
};

class Chess_Window : public Fl_Double_Window
{
public:
	Chess_Window(int x, int y, int w, int h, const char *l = 0);
	void button_skin(int id);
	void grid_num_color();
	void skin_wood();
	void skin_sky();
	void skin_change();
	void diag_hs();	//diag hide or show
	void num_effect(int i, int j);	//grid number effect
	void num_normal();
	Grid *grid;
	My_Button *start, *end, *retract, *next, *back, *load, *save, *number, *skin, *manual, *diag;
	vector<My_Button *> button_list;
	Fl_Choice *gtype, *player;
	Fl_Box *skin_box, *status, *about, *time, *diag_box, *score, *type_box;
	Fl_JPEG_Image *skin_img_wood, *skin_img_sky, *button_img[3];
	Fl_GIF_Image *black_img, *white_img;
	Square *square, *square2;	//hint square, last square
	char time_st[3], score_st[30];
	int skin_id, button_skin_id;
	Fl_Box *num1, *num2;	//grid number effect box
	Fl_Box *num_h[15], *num_v[15];	//horizontal i
	Fl_Color effect_color, grid_color;
	bool if_diag;
};

extern Chess_Window mywin;

class Chess
{
public:
	Chess();
	void start();
	void end();
	void retract();
	void back();
	void next();
	void load();
	void save();
	void show_num();
	void hide_num();
	void number();
	void manual_auto();
	void time_dec();
	void gtype1();	//1 player
	void gtype2();	//2 player
	void pblack();	//player choose black in single player type
	void pwhite();	//player choose white in single player type
	void move(int i, int j);
	void hint(int i, int j);	//tell player where the cursor is
	bool active;	//whether active
private:
	Color win(int ii, int jj);	//return Black, White or Draw
	void print_score();
	void print_winner(Color winner);
	bool con_h(int n, int i1, int i2, int j, Color c);	//horizontal
	bool con_v(int n, int i, int j1, int j2, Color c);	//vertical
	bool con_1(int n, int i1, int j1, int i2, int j2, Color c);	//(0,0) (1,1) direction
	bool con_2(int n, int i1, int j1, int i2, int j2, Color c);	//(0,1) (1,0) derection
	bool dead_b(int i1, int j1, int i2, int j2, Color c);	//dead border : be intercepted by c in one side
	int live(int n, int i, int j);	//the number of "living n", n=2,3,4 
	int dead(int n, int i, int j);	
	void evaluate(Color color, int v[15][15]);	//evaluate the situation
	void AI(Color color);
	Color now;	//whose turn
	Color ai;	//color of AI
	Color g[15][15];	//chessboard
	int vb[15][15], vw[15][15];		//value
	vector<move_t> moves;
	vector<Fl_Box *> moves_box;	//save qizi
	int step, time, score1, score2;	//step starts from 0
	char num[250][5];
	bool if_num, if_manual;
};

extern Chess chess;

void start_cb(Fl_Widget *, void *);

void end_cb(Fl_Widget *, void *);

void retract_cb(Fl_Widget *, void *);

void back_cb(Fl_Widget *, void *);

void next_cb(Fl_Widget *, void *);

void load_cb(Fl_Widget *, void *);

void save_cb(Fl_Widget *, void *);

void number_cb(Fl_Widget *, void *);

void skin_cb(Fl_Widget *, void *);

void manual_auto_cb(Fl_Widget *, void *);

void diag_cb(Fl_Widget *, void *);

void gtype1_cb(Fl_Widget *, void *);

void gtype2_cb(Fl_Widget *, void *);

void pblack_cb(Fl_Widget *, void *);

void pwhite_cb(Fl_Widget *, void *);

void time_cb(void *);

void auto_next_cb(void *);
