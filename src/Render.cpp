#include "../include/Render.h"
using namespace std;

constexpr size_t X = 0;
constexpr size_t Y = 1;

void Render(Ball* ball_ins, vector<RECT> block_list) {
	MoveByTime(ball_ins);
	setfillcolor(WHITE);

	for_each(block_list.cbegin(),
			 block_list.cend(),
			 [] (const RECT block) {
				 solidrectangle(
					 (int)block.left,
					 (int)block.top,
					 (int)block.right,
					 (int)block.bottom
				 );
			 });

	auto ball_pos = ball_ins->GetPosition();
	solidcircle((int)ball_pos[X], (int)ball_pos[Y], RADIUS);
	Sleep((unsigned int)15);
}

void MoveByTime(Ball* ball_ins, float time) {
	ball_ins->Move(time);
}