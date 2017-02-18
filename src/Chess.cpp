#include "Chess.h"

void Square::draw()
{
	fl_color(effect_color);
	fl_rect(x(), y(), w(), h());
}

Chess_Window::Chess_Window(int x, int y, int w, int h, const char *l) : Fl_Double_Window(x, y, w, h, l)
{
	skin_img_wood = new Fl_JPEG_Image("pic/wood.jpg");
	skin_img_sky = new Fl_JPEG_Image("pic/sky.jpg");
	skin_box = new Fl_Box(0, 0, 800, 600);
	skin_box->image(skin_img_wood);
	skin_id = 0;

	black_img = new Fl_GIF_Image("pic/black.gif");
	white_img = new Fl_GIF_Image("pic/white.gif");
	square = new Square(0, 0, 0);
	square2 = new Square(0, 0, 0);
	
	grid = new Grid;
	grid_color = FL_BLACK;

	for (int i = 0; i < 15; i++)
	{
		char *c = (char *)malloc(3*sizeof(char));
		if (i < 10)
		{
			c[0] = '0'+i;
			c[1] = '\0';
		}
		else
		{
			c[0] = '1';
			c[1] = '0'+i-10;
			c[2] = '\0';
		}
		num_h[i] = new Fl_Box(x_begin - 2 + Gap * i, y_begin - 30, 4, 4, c);
		num_v[i] = new Fl_Box(x_begin - 30, y_begin - 2 + Gap * i, 4, 4, c);
	}
	effect_color = FL_BLUE;

	start = new My_Button(600, 50, 80, 25, "Start");
	start->image(white_img);
	start->callback(start_cb);

	end = new My_Button(700, 50, 80, 25, "End");
	end->callback(end_cb);
	end->deactivate();

	retract = new My_Button(600, 100, 80, 25, "Retract");
	retract->callback(retract_cb);
	retract->deactivate();

	back = new My_Button(600, 100, 80, 25, "Back");
	back->callback(back_cb);
	back->hide();

	next = new My_Button(700, 100, 80, 25, "Next");
	next->callback(next_cb);
	next->deactivate();

	load = new My_Button(600, 150, 80, 25, "Load");
	load->callback(load_cb);

	save = new My_Button(700, 150, 80, 25, "Save");
	save->callback(save_cb);

	number = new My_Button(600, 200, 80, 25, "Number");
	number->callback(number_cb);

	skin = new My_Button(700, 200, 80, 25, "Skin");
	skin->callback(skin_cb);

	manual = new My_Button(600, 250, 80, 25, "Manual");
	manual->deactivate();
	manual->callback(manual_auto_cb);

	diag = new My_Button(700, 250, 80, 25, "Dialog");
	diag->callback(diag_cb);
	if_diag = false;

	button_list.push_back(start);
	button_list.push_back(end);
	button_list.push_back(retract);
	button_list.push_back(back);
	button_list.push_back(next);
	button_list.push_back(load);
	button_list.push_back(save);
	button_list.push_back(number);
	button_list.push_back(skin);
	button_list.push_back(manual);
	button_list.push_back(diag);
	
	button_img[0] = new Fl_JPEG_Image("pic/button0.jpg");
	button_img[1] = new Fl_JPEG_Image("pic/button1.jpg");
	button_img[2] = new Fl_JPEG_Image("pic/button2.jpg");
	button_skin(0);

	gtype = new Fl_Choice(700, 300, 80, 25, "Type");	//game type
	gtype->add("1 Player", 0, gtype1_cb);
	gtype->add("2 Player", 0, gtype2_cb);
	gtype->value(0);

	player = new Fl_Choice(700, 340, 80, 25, "Player");
	player->add("Black", 0, pblack_cb);
	player->add("White", 0, pwhite_cb);
	player->value(0);

	status = new Fl_Box(660, 575, 130, 25, "Status: Off");
	status->align(FL_ALIGN_INSIDE + FL_ALIGN_RIGHT);

	about = new Fl_Box(660, 0, 130, 25, "Chess 1.1 by yfy");
	about->align(FL_ALIGN_INSIDE + FL_ALIGN_RIGHT);

	strcpy(score_st, "Score(b/w) 0:0");
	score = new Fl_Box(10, 575, 150, 25, score_st);
	score->align(FL_ALIGN_INSIDE + FL_ALIGN_LEFT);

	diag_box = new Fl_Box(600, 400, 180, 100, "??:\n    \344\275\240\345\245\275\345\221\200!");
	diag_box->hide();
	diag_box->labelcolor(FL_YELLOW);
	diag_box->labelsize(15);
	diag_box->align(FL_ALIGN_LEFT + FL_ALIGN_TOP + FL_ALIGN_INSIDE);
	diag_box->box(FL_FLAT_BOX);
	diag_box->color(FL_BLACK);

	type_box = new Fl_Box(360, 575, 100, 25, "Type: 1 Player");

	time = new Fl_Box(600, 300, 30, 30);
	time->hide();
	time->labelcolor(FL_YELLOW);
	time->labelsize(20);
	time->box(FL_FLAT_BOX);
	time->color(FL_BLACK);
}

void Chess_Window::button_skin(int id)
{
	for (int i = 0; i < button_list.size(); i++)
	{
		button_list[i]->image(button_img[id]);
		button_list[i]->labelcolor(button_label_color[id]);
	}
}

void Chess_Window::grid_num_color()
{
	for (int i = 0; i < 15; i++)
	{
		num_h[i]->labelcolor(grid_color);
		num_v[i]->labelcolor(grid_color);
	}
}

void Chess_Window::skin_wood()
{
	skin_box->image(skin_img_wood);
	grid_color = FL_BLACK;
	grid_num_color();
	effect_color = FL_BLUE;
	gtype->labelcolor(FL_BLACK);
	player->labelcolor(FL_BLACK);
	about->labelcolor(FL_BLACK);
	score->labelcolor(FL_BLACK);
	type_box->labelcolor(FL_BLACK);
	status->labelcolor(FL_BLACK);
	square->effect_color = square2->effect_color = FL_BLUE;
	redraw();
}

void Chess_Window::skin_sky()
{
	skin_box->image(skin_img_sky);
	grid_color = 39;
	grid_num_color();
	effect_color = FL_YELLOW;
	gtype->labelcolor(grid_color);
	player->labelcolor(grid_color);
	about->labelcolor(grid_color);
	score->labelcolor(FL_YELLOW);
	type_box->labelcolor(FL_YELLOW);
	status->labelcolor(FL_YELLOW);
	square->effect_color = square2->effect_color = FL_YELLOW;
	redraw();
}

void Chess_Window::skin_change()
{
	switch(skin_id)
	{
	case 0:
		skin_id++;
		skin_sky();
		break;
	case 1:
		skin_id = 0;
		skin_wood();
		break;
	}

	if (button_skin_id < 2)
		button_skin_id++;
	else
		button_skin_id = 0;
	button_skin(button_skin_id);
}

void Chess_Window::diag_hs()
{
	if (if_diag)
	{
		diag_box->hide();
		if_diag = false;
	}
	else
	{
		diag_box->show();
		if_diag = true;
	}
}

void Chess_Window::num_effect(int i, int j)
{
	if (!chess.active) return;
	num_normal();
	num_h[i]->labelsize(18);
	num_h[i]->labelcolor(effect_color);
	num_v[j]->labelsize(18);
	num_v[j]->labelcolor(effect_color);
	num1 = num_h[i];
	num2 = num_v[j];
}

void Chess_Window::num_normal()
{
	if (num1)
	{
		num1->labelsize(14);
		num1->labelcolor(grid_color);
		num1 = NULL;
	}
	if (num2)
	{
		num2->labelsize(14);
		num2->labelcolor(grid_color);
		num2 = NULL;
	}
}

Chess::Chess()
{
	ai = White;
	active = false;
	score1 = score2 = 0;
	if_num = false;
}

Color Chess::win(int ii, int jj)
{
	int i, j, i_begin, i_end, j_begin, j_end, len1, len2, len;

	i_begin = ii - 4;
	if (i_begin < 0) i_begin = 0;
	i_end = ii + 4;
	if (i_end > 14) i_end = 14;
	len = 1;
	for (i = i_begin + 1; i <= i_end; i++)
	{
		if (g[i][jj] == Empty) continue;
		if (g[i][jj] == g[i-1][jj])
		{
			len++;
			if (len == 5) return g[i][jj];
		}
		else len = 1;
	}

	j_begin = jj - 4;
	if (j_begin < 0) j_begin = 0;
	j_end = jj + 4;
	if (j_end > 14) j_end = 14;
	len = 1;
	for (j = j_begin + 1; j <= j_end; j++)
	{
		if (g[ii][j] == Empty) continue;
		if (g[ii][j] == g[ii][j-1])
		{
			len++;
			if (len == 5) return g[ii][j];
		}
		else len = 1;
	}

	len1 = min(ii - i_begin, jj - j_begin);
	len2 = min(i_end - ii, j_end - jj);
	len = 1;
	for (i = -len1 + 1; i <= len2; i++)
	{
		if (g[ii+i][jj+i] == Empty) continue;
		if (g[ii+i][jj+i] == g[ii+i-1][jj+i-1])
		{
			len++;
			if (len == 5) return g[ii][jj];
		}
		else len = 1;
	}

	len1 = min(ii - i_begin, j_end - jj);
	len2 = min(i_end - ii, jj - j_begin);
	len = 1;
	for (i = -len1 + 1; i <= len2; i++)
	{
		if (g[ii+i][jj-i] == Empty) continue;
		if (g[ii+i][jj-i] == g[ii+i-1][jj-i+1])
		{
			len++;
			if (len == 5) return g[ii][jj];
		}
		else len = 1;
	}

	if (moves.size() == 15 * 15) return Draw; else return Empty;
}

void Chess::print_score()
{
	char *st = mywin.score_st;
	sprintf(st, "Score(b/w) %d:%d", score1, score2);
	mywin.score->label(st);
}

void Chess::print_winner(Color winner)
{
	end();
	if (ai != Empty)
		if (ai == winner)
			mywin.diag_box->label("??:\n    Too young...\n    Too simple...");
		else
			mywin.diag_box->label("??:\n    \344\271\237\344\270\215\350\256\251\350\256\251\344\274\246\345\256\266...\345\221\234\345\221\234...");
	switch (winner)
	{
	case Black:
		mywin.status->label("Status: Black Win");
		score1++;
		fl_message("Black Win!");
		break;
	case White:
		mywin.status->label("Status: White Win");
		score2++;
		fl_message("White Win!");
		break;
	case Draw:
		mywin.status->label("Status: Draw");
		fl_message("Draw!");
		break;
	}
	print_score();
}

void Chess::move(int i, int j)
{
	if (!active) return;
	if (g[i][j] != Empty) return;

	move_t p;
	p.i = i;
	p.j = j;
	Fl_Box *box = new Fl_Box(x_begin + Gap * i - int(Gap/2), y_begin + Gap * j - int(Gap/2), Gap, Gap);
	box->align(FL_ALIGN_IMAGE_BACKDROP);
	if (now == Black)
	{
		box->image(mywin.black_img);
		g[i][j] = now;
		now = White;
		mywin.status->label("Status: White Turn");
		mywin.redraw();
	}
	else
	{
		box->image(mywin.white_img);
		g[i][j] = now;
		now = Black;
		mywin.status->label("Status: Black Turn");
		mywin.redraw();
	}
	moves.push_back(p);
	moves_box.push_back(box);
	mywin.add(box);
	if (if_num)
	{
		int step = moves_box.size()-1;
		sprintf(num[step], "%d", step + 1);
		if (box->image() == mywin.black_img)
			box->labelcolor(FL_WHITE);
		else
			box->labelcolor(FL_BLACK);
		box->label(num[step]);
	}
	mywin.square2->resize(x_begin + Gap * i - int(Gap/2), y_begin + Gap * j - int(Gap/2), Gap, Gap);
	mywin.retract->activate();
	mywin.save->activate();
	mywin.redraw();

	time = 60;
	time_dec();

	Color winner = win(i, j);
	if (winner == Empty) 
	{
		if (ai == now) AI(now);
		return;
	}
	print_winner(winner);

}

void Chess::hint(int i, int j)
{
	if (!active) return;
	mywin.square->resize(x_begin + Gap * i - int(Gap/2), y_begin + Gap * j - int(Gap/2), Gap, Gap);
	mywin.square->redraw();
	mywin.redraw();
}

void Chess::start()
{
	end();
	memset(&g, Empty, sizeof(Color)*225);
	moves.clear();
	while (moves_box.size() > 0)
	{
		Fl_Box *b = moves_box[moves_box.size()-1];
		mywin.remove(b);
		moves_box.pop_back();
		delete b;
	}
	mywin.square2->resize(0, 0, 0, 0);
	mywin.end->activate();
	mywin.retract->show();
	mywin.retract->deactivate();
	mywin.back->hide();
	mywin.next->deactivate();
	mywin.save->deactivate();
	mywin.manual->deactivate();
	mywin.gtype->hide();
	mywin.player->hide();
	mywin.type_box->show();

	active = true;
	now = Black;
	mywin.status->label("Status: Black Turn");
	mywin.diag_box->label("??:\n    \344\275\240\345\245\275\345\221\200!");
	mywin.time->show();
	time = 60;
	time_dec();
	mywin.redraw();
	if (ai == now) AI(now);
}

void Chess::end()
{
	Fl::remove_timeout(time_cb);
	Fl::remove_timeout(auto_next_cb);
	mywin.time->hide();
	active = false;
	mywin.end->deactivate();
	mywin.retract->deactivate();
	mywin.back->deactivate();
	mywin.next->deactivate();
	mywin.manual->deactivate();
	mywin.status->label("Status: Off");
	mywin.gtype->show();
	mywin.player->show();
}

void Chess::retract()
{
	if (moves.size() == 1 && ai == Black) return;
	int i, n;
	move_t p;
	Fl_Box *b;
	active = true;
	if (ai == Empty || now == ai) n = 1; else n = 2;
	for (i = 0; i < n; i++)
	{
		p = moves[moves.size()-1];
		b = moves_box[moves_box.size()-1];
		mywin.remove(b);
		g[p.i][p.j] = Empty;
		moves.pop_back();
		moves_box.pop_back();
		delete b;
		now = now == Black ? White : Black;
	}
	if (moves.size() == 0) mywin.retract->deactivate();
	if (now == Black) mywin.status->label("Status: Black Turn"); else mywin.status->label("Status: White Turn");
	if (moves.size() == 0)
		mywin.square2->resize(0, 0, 0, 0);
	else
		mywin.square2->resize(x_begin + Gap * moves[moves.size()-1].i - int(Gap/2), y_begin + Gap * moves[moves.size()-1].j - int(Gap/2), Gap, Gap);
	mywin.redraw();

	time = 60;
	time_dec();
}

void Chess::back()
{
	moves_box[step]->hide();
	step--;
	mywin.next->activate();
	if (step == -1) mywin.back->deactivate();
}

void Chess::next()
{
	if (step == moves_box.size() - 1) return;
	step++;
	moves_box[step]->show();
	mywin.back->activate();
	if (step == moves_box.size()-1) mywin.next->deactivate();
}

void Chess::load()
{
	Fl_Native_File_Chooser fc;
	fc.title("Load");
	fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fc.filter("Chess Record File(*.crf)\t*.crf");
	fc.directory(".\\");
	if (fc.show() == 0)
	{
		active = false;

		Fl::remove_timeout(time_cb);
		mywin.time->hide();

		memset(&g, Empty, sizeof(Color) * 225);
		moves.clear();
		while (moves_box.size() > 0)
		{
			Fl_Box *b = moves_box[moves_box.size()-1];
			mywin.remove(b);
			moves_box.pop_back();
			delete b;
		}
		mywin.square2->resize(0, 0, 0, 0);
		
		mywin.status->label("Status: Replay");
		mywin.end->activate();
		mywin.retract->hide();
		mywin.back->show();
		mywin.back->deactivate();
		mywin.next->activate();
		mywin.save->deactivate();
		mywin.manual->activate();
		mywin.gtype->hide();
		mywin.player->hide();
		mywin.type_box->hide();

		int size;
		move_t m;
		Color now = Black;
		Fl_Box *box;
		const char *filename = fc.filename();
		FILE *f = fopen(filename, "rb");
		fread(&size, sizeof(int), 1, f);
		for (int i = 0; i < size; i++)
		{
			fread(&m, sizeof(move_t), 1, f);
			box = new Fl_Box(x_begin + Gap * m.i - int(Gap/2), y_begin + Gap * m.j - int(Gap/2), Gap, Gap);
			box->align(FL_ALIGN_IMAGE_BACKDROP);
			if (now == Black)
			{
				box->image(mywin.black_img);
				now = White;
			}
			else
			{
				box->image(mywin.white_img);
				now = Black;
			}
			mywin.add(box);
			box->hide();
			moves_box.push_back(box);
		}
		if (if_num) show_num();
		step = -1;
		if_manual = true;
	}
}

void Chess::save()
{
	Fl_Native_File_Chooser fc;
	fc.title("Save");
	fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	fc.filter("Chess Record File(*.crf)\t*.crf");
	fc.directory(".\\");
	if (fc.show() == 0 && moves.size() > 0)
	{
		FILE *f;
		int len, size;
		char *filename;
		const char *name = fc.filename();
		len = strlen(name);
		filename = new char[len+5];
		memcpy(filename, name, len+1);
		char suffix[] = ".crf";
		if (name[len-4] == '.' && name[len-3] == 'c' && name[len-2] == 'r' && name[len-1] == 'f')
		{
			f = fopen(filename, "wb");
		}
		else
		{
			strcat(filename, suffix);
			f = fopen(filename, "wb");
		}
		size = moves.size();
		fwrite(&size, sizeof(int), 1, f);
		fwrite(&moves[0], sizeof(move_t), moves.size(), f);
		fclose(f);
	}
}

void Chess::show_num()
{
	for (int i = 0; i < moves_box.size(); i++)
	{
		sprintf(num[i], "%d", i + 1);
		Fl_Box *box = moves_box[i];
		if (box->image() == mywin.black_img)
			box->labelcolor(FL_WHITE);
		else
			box->labelcolor(FL_BLACK);
		box->label(num[i]);
	}
	if_num = true;
}

void Chess::hide_num()
{
	for (int i = 0; i < moves_box.size(); i++)
	{
		moves_box[i]->label(NULL);
	}
	if_num = false;
}

void Chess::number()
{
	if (chess.if_num) chess.hide_num(); else chess.show_num();
}

void Chess::manual_auto()
{
	if (if_manual)
	{
		if_manual = false;
		mywin.manual->label("Auto");
		auto_next_cb(NULL);
	}
	else
	{
		if_manual = true;
		mywin.manual->label("Manual");
		Fl::remove_timeout(auto_next_cb);
	}
}

void Chess::time_dec()
{
	char *st = mywin.time_st;
	st[0] = int(time / 10) + '0';
	st[1] = time % 10 + '0';
	st[2] = '\0';
	mywin.time->label(st);
	if (time == 0)
	{
		print_winner(now == Black ? White : Black);
		return;
	}
	if (time == 10)
		mywin.diag_box->label("??:\n    \345\277\253\344\270\200\347\202\271\345\223\246");
	time--;
	Fl::repeat_timeout(1, time_cb);
}

void Chess::gtype1()
{
	if (mywin.player->value() == 0) ai = White; else ai = Black;
	mywin.player->show();
	mywin.type_box->label("Type: 1 Player");
	mywin.redraw();
}

void Chess::gtype2()
{
	ai = Empty;
	mywin.player->hide();
	mywin.type_box->label("Type: 2 Player");
	mywin.redraw();
}

void Chess::pblack()
{
	ai = White;
}

void Chess::pwhite()
{
	ai = Black;
}

bool Chess::con_h(int n, int i1, int i2, int j, Color c)
{
	if (!(g[i1][j] == c && g[i2][j] == c)) return false;
	int i, len;
	len = 0;
	for (i = i1; i <= i2; i++)
		if (g[i][j] == c) len++;
		else if (g[i][j] != Empty) return false;
	if (len == n) return true; else return false;
}

bool Chess::con_v(int n, int i, int j1, int j2, Color c)
{
	if (!(g[i][j1] == c && g[i][j2] == c)) return false;
	int j, len;
	len = 0;
	for (j = j1; j <= j2; j++)
		if (g[i][j] == c) len++;
		else if (g[i][j] != Empty) return false;
	if (len == n) return true; else return false;
}

bool Chess::con_1(int n, int i1, int j1, int i2, int j2, Color c)
{
	if (!(g[i1][j1] == c && g[i2][j2] == c)) return false;
	int i, j, len;
	len = 0;
	i = i1;
	j = j1;
	while (i <= i2)
	{
		if (g[i][j] == c) len++;
		else if (g[i][j] != Empty) return false;
		i++;
		j++;
	}
	if (len == n) return true; else return false;
}

bool Chess::con_2(int n, int i1, int j1, int i2, int j2, Color c)
{
	if (!(g[i1][j1] == c && g[i2][j2] == c)) return false;
	int i, j, len;
	len = 0;
	i = i1;
	j = j1;
	while (i <= i2)
	{
		if (g[i][j] == c) len++;
		else if (g[i][j] != Empty) return false;
		i++;
		j--;
	}
	if (len == n) return true; else return false;
}

bool Chess::dead_b(int i1, int j1, int i2, int j2, Color c)
{
	bool in1, in2;
	in1 = (i1 >= 0 && i1 <= 14 && j1 >= 0 && j1 <= 14);
	in2 = (i2 >= 0 && i2 <= 14 && j2 >= 0 && j2 <= 14);
	if (in1 && !g[i1][j1] && (in2 && g[i2][j2] == c || !in2) ||
		in2 && !g[i2][j2] && (in1 && g[i1][j1] == c || !in1)) return true;
	return false;
}

int Chess::live(int n, int i, int j)
{
	int a, num;
	Color c, rival;
	c = g[i][j];
	num = 0;
	rival = c == Black ? White : Black;
	for (a = 1; a <= n; a++)
	{
		if (i-a+1 > 0 && i+n-a < 14 && con_h(n, i-a+1, i+n-a, j, c) && !g[i-a][j] && !g[i+n-a+1][j]) num++;
		if (j-a+1 > 0 && j+n-a < 14 && con_v(n, i, j-a+1, j+n-a, c) && !g[i][j-a] && !g[i][j+n-a+1]) num++;
		if (i-a+1 > 0 && i+n-a < 14 && j-a+1 > 0 && j+n-a < 14 && con_1(n, i-a+1, j-a+1, i+n-a, j+n-a, c) && !g[i-a][j-a] && !g[i+n-a+1][j+n-a+1]) num++;
		if (i-a+1 > 0 && i+n-a < 14 && j+a-1 < 14 && j-n+a > 0 && con_2(n, i-a+1, j+a-1, i+n-a, j-n+a, c) && !g[i-a][j+a] && !g[i+n-a+1][j-n+a-1]) num++;
	}
	if (n == 3)
		for (a = 1; a <= n+1; a++)
		{
			if (i-a+1 > 0 && i+n-a+1 < 14 && con_h(n, i-a+1, i+n-a+1, j, c) && !g[i-a][j] && !g[i+n-a+2][j]) num++;
			if (j-a+1 > 0 && j+n-a+1 < 14 && con_v(n, i, j-a+1, j+n-a+1, c) && !g[i][j-a] && !g[i][j+n-a+2]) num++;
			if (i-a+1 > 0 && i+n-a+1 < 14 && j-a+1 > 0 && j+n-a+1 < 14 && con_1(n, i-a+1, j-a+1, i+n-a+1, j+n-a+1, c) && !g[i-a][j-a] && !g[i+n-a+2][j+n-a+2]) num++;
			if (i-a+1 > 0 && i+n-a+1 < 14 && j+a-1 < 14 && j-n+a-1 > 0 && con_2(n, i-a+1, j+a-1, i+n-a+1, j-n+a-1, c) && !g[i-a][j+a] && !g[i+n-a+2][j-n+a-2]) num++;
		}
	return num;
}

int Chess::dead(int n, int i, int j)
{
	int a, num;
	Color c, rival;
	c = g[i][j];
	rival = c == Black ? White : Black;
	num = 0;
	for (a = 1; a <= n; a++)
	{
		if (i-a+1 >= 0 && i+n-a <= 14 && con_h(n, i-a+1, i+n-a, j, c) && dead_b(i-a, j, i+n-a+1, j, rival)) num++;
		if (j-a+1 >= 0 && j+n-a <= 14 && con_v(n, i, j-a+1, j+n-a, c) && dead_b(i, j-a, i, j+n-a+1, rival)) num++;
		if (i-a+1 >= 0 && i+n-a <= 14 && j-a+1 >= 0 && j+n-a <= 14 && con_1(n, i-a+1, j-a+1, i+n-a, j+n-a, c) && dead_b(i-a, j-a, i+n-a+1, j+n-a+1, rival)) num++;
		if (i-a+1 >= 0 && i+n-a <= 14 && j+a-1 <= 14 && j-n+a >= 0 && con_2(n, i-a+1, j+a-1, i+n-a, j-n+a, c) && dead_b(i-a, j+a, i+n-a+1, j-n+a-1, rival)) num++;
	}
	if (n == 3)
		for (a = 1; a <= n+1; a++)
		{
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && con_h(n, i-a+1, i+n-a+1, j, c) && dead_b(i-a, j, i+n-a+2, j, rival)) num++;
			if (j-a+1 >= 0 && j+n-a+1 <= 14 && con_v(n, i, j-a+1, j+n-a+1, c) && dead_b(i, j-a, i, j+n-a+2, rival)) num++;
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && j-a+1 >= 0 && j+n-a+1 <= 14 && con_1(n, i-a+1, j-a+1, i+n-a+1, j+n-a+1, c) && dead_b(i-a, j-a, i+n-a+2, j+n-a+2, rival)) num++;
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && j+a-1 <= 14 && j-n+a-1 >= 0 && con_2(n, i-a+1, j+a-1, i+n-a+1, j-n+a-1, c) && dead_b(i-a, j+a, i+n-a+2, j-n+a-2, rival)) num++;
		}
	if (n == 4)
		for (a = 1; a <= n+1; a++)
		{
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && con_h(n, i-a+1, i+n-a+1, j, c)) num++;
			if (j-a+1 >= 0 && j+n-a+1 <= 14 && con_v(n, i, j-a+1, j+n-a+1, c)) num++;
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && j-a+1 >= 0 && j+n-a+1 <= 14 && con_1(n, i-a+1, j-a+1, i+n-a+1, j+n-a+1, c)) num++;
			if (i-a+1 >= 0 && i+n-a+1 <= 14 && j+a-1 <= 14 && j-n+a-1 >= 0 && con_2(n, i-a+1, j+a-1, i+n-a+1, j-n+a-1, c)) num++;
		}
	return num;
}

void Chess::evaluate(Color color, int v[15][15])
{
	int i, j, y2, n2, y3, n3, y4, n4;
	Color rival;
	if (color == Black)	rival = White; else rival = Black;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (g[i][j] != Empty) 
			{
				v[i][j] = 0;
				continue;
			}
			g[i][j] = color;
			y2 = live(2, i, j);
			n2 = dead(2, i, j);
			y3 = live(3, i, j);
			n3 = dead(3, i, j);
			y4 = live(4, i, j);
			n4 = dead(4, i, j);
			if (win(i, j) == color) v[i][j] = 11;
			else if (y4) v[i][j] = 10;
			else if (n4 > 1 || n4 && y3) v[i][j] = 9;
			else if (y3 > 1) v[i][j] = 8;
			else if (n3 && y3) v[i][j] = 7;
			else if (n4 || y3) v[i][j] = 6;
			//else if () v[i][j] = 5;
			else if (y2 > 1) v[i][j] = 4;
			else if (n3) v[i][j] = 3;
			else if (y2) v[i][j] = 2;
			else if (n2) v[i][j] = 1;
			else v[i][j] = 0;
			g[i][j] = Empty;
		}
}

void Chess::AI(Color color)
{
	int i, j, max_b, max_w, max_bi, max_bj, max_wi, max_wj; 
	evaluate(Black, vb);
	evaluate(White, vw);

	max_b = 0;
	max_bi = 0;
	max_bj = 0;
	max_w = 0;
	max_wi = 0;
	max_wj = 0;
	for (i = 0; i < 15; i++)
		for (j = 0; j < 15; j++)
		{
			if (vb[i][j] > max_b || vb[i][j] == max_b && abs(i-7)+abs(j-7) < abs(max_bi-7)+abs(max_bj-7))
			{
				max_b = vb[i][j];
				max_bi = i;
				max_bj = j;
			}
			if (vw[i][j] > max_w || vw[i][j] == max_w && abs(i-7)+abs(j-7) < abs(max_wi-7)+abs(max_wj-7))
			{
				max_w = vw[i][j];
				max_wi = i;
				max_wj = j;
			}
		}
	if (max_b > max_w) move(max_bi, max_bj);
	else if (max_b < max_w) move(max_wi, max_wj);
	else if (color == Black) move(max_bi, max_bj); else move(max_wi, max_wj);
}

void Grid::draw()
{
	int i, x, y, x_end, y_end;

	x = x_begin;
	y = y_begin;
	x_end = x_begin + Gap * 14;
	y_end = y_begin + Gap * 14;
	
	fl_color(mywin.grid_color);
	for (i = 0; i < 15; i++)
	{
		fl_line(x_begin, y, x_end, y);
		fl_line(x, y_begin, x, y_end);
		x += Gap;
		y += Gap;
	}
}

int Grid::handle(int e)
{
	int i, j;
	switch(e)
	{
	case FL_PUSH:
		i = int((Fl::event_x() - x_begin + int(Gap/2)) / Gap);
		j = int((Fl::event_y() - y_begin + int(Gap/2)) / Gap);
		chess.move(i, j);
		return 1;
	case FL_ENTER:
		return 1;
	case FL_MOVE:
		i = int((Fl::event_x() - x_begin + int(Gap/2)) / Gap);
		j = int((Fl::event_y() - y_begin + int(Gap/2)) / Gap);
		chess.hint(i, j);
		mywin.num_effect(i, j);
		return 1;
	case FL_LEAVE:
		mywin.square->resize(0, 0, 0, 0);
		mywin.num_normal();
		mywin.redraw();
		return 1;
	}
	return 0;
}

void start_cb(Fl_Widget *, void *)
{
	chess.start();
}

void end_cb(Fl_Widget *, void *)
{
	chess.end();
}

void retract_cb(Fl_Widget *, void *)
{
	chess.retract();
}

void back_cb(Fl_Widget *, void *)
{
	chess.back();
}

void next_cb(Fl_Widget *, void *)
{
	chess.next();
}

void load_cb(Fl_Widget *, void *)
{
	chess.load();
}

void save_cb(Fl_Widget *, void *)
{
	chess.save();
}

void number_cb(Fl_Widget *, void *)
{
	chess.number();
}

void skin_cb(Fl_Widget *, void *)
{
	mywin.skin_change();
}

void manual_auto_cb(Fl_Widget *, void *)
{
	chess.manual_auto();
}

void diag_cb(Fl_Widget *, void *)
{
	mywin.diag_hs();
}

void gtype1_cb(Fl_Widget *, void *)
{
	chess.gtype1();
}

void gtype2_cb(Fl_Widget *, void *)
{
	chess.gtype2();
}

void pblack_cb(Fl_Widget *, void *)
{
	chess.pblack();
}

void pwhite_cb(Fl_Widget *, void *)
{
	chess.pwhite();
}

void time_cb(void *)
{
	Fl::remove_timeout(time_cb);
	chess.time_dec();
}

void auto_next_cb(void *)
{
	chess.next();
	Fl::repeat_timeout(1, auto_next_cb);
}
