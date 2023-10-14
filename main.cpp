#include <iostream>
#include <graphics.h>
#include "include/Render.h"
#include "include/Ball.h"

using namespace std;

constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;

int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	BeginBatchDraw();

	auto ball_ptr = new Ball(
		WINDOW_WIDTH / 2, 
		WINDOW_HEIGHT / 2,
		1.f,
		1.f);
	vector<RECT> block_list{
		{-10, -10, 0, WINDOW_HEIGHT},								// ×óÇ½±Ú
		{0, -10, WINDOW_WIDTH + 10, 0},								// ÉÏÇ½±Ú
		{WINDOW_WIDTH, 0, WINDOW_WIDTH + 10, WINDOW_HEIGHT + 10},	// ÓÒÇ½±Ú
		{-10, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT + 10}		// ÏÂÇ½±Ú
	};
	while (true) {
		cleardevice();
		Render(ball_ptr, block_list);
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}