#include "../include/Render.h"
#include "../include/Physics.h"
using namespace std;

constexpr size_t X = 0;
constexpr size_t Y = 1;

void Render(Ball* ball_ins, vector<RECT> block_list) {
	MoveByTime(ball_ins);
	auto collision_status = FrameCollisionCheck(ball_ins, block_list);
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
	if (collision_status == true) {
		setfillcolor(GREEN);
	}
	auto ball_pos = ball_ins->GetPosition();
	solidcircle((int)ball_pos[X], (int)ball_pos[Y], static_cast<int>(ball_ins->GetRadius()));
	// TODO: Ö¡ÂÊ¿ØÖÆ
	Sleep((unsigned int)30);
}

void MoveByTime(Ball* ball_ins, float time) {
	ball_ins->Move(time);
}

bool FrameCollisionCheck(Ball* ball_ins, vector<RECT> block_list) {
	constexpr unsigned int check_time = 3;
	bool is_collision = false;
	srand((unsigned)time(NULL));
	for (unsigned int k = 0; k < check_time; ++k) {
		for_each(block_list.cbegin(),
				 block_list.cend(),
				 [&ball_ins, &is_collision] (const RECT block) {
					 if (CollisionCheck(block, ball_ins) && !is_collision) {
						 is_collision = true;
					 }
				 });
		ball_ins->Move(ball_ins->GetPosition().at(X) + ball_ins->GetSpeed().at(X) + (rand() % 10) / 100.f,
					   ball_ins->GetPosition().at(Y) + ball_ins->GetSpeed().at(Y) + (rand() % 10) / 100.f);
	}
	return is_collision;
}