#define NOMINMAX
#include "SimpleVoronoiIsland.hpp"
#include "DungeonTemplateOutput.hpp"
#include <DxLib.h>
#include <array>
#include <bitset>

//����ʃT�C�Y
constexpr std::int_fast32_t window_map_size_x{ 256 };

//�c��ʃT�C�Y
constexpr std::int_fast32_t window_map_size_y{ 256 };

//�o��
template<typename Vector_>
void output(const Vector_& vec_) {
	for (size_t y{}; y < vec_.size(); ++y) {
		for (size_t x{}; x < vec_[y].size(); ++x) {
			if (vec_[y][x]) DrawPixel((int)x, (int)y, GetColor(63, 155, 76));//63, 155, 76//119,103,52
			else DrawPixel((int)x, (int)y, GetColor(47, 104, 173));//97, 154, 223//208, 187 - rnd(20), 122 - rnd(20)
		}
	}
}
//���C�����[�v
bool mainLoop() {
	return (ScreenFlip() == 0 && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0);
}

void VMain() {
	//�{���m�C�}�����
	dtl::SimpleVoronoiIsland<bool> diagram;
	//�}�b�v�i�[�z��
	std::array<std::bitset<window_map_size_x>, window_map_size_y> col{ {} };
	//�X�V����
	constexpr std::int_fast32_t max_time{ 20 };
	std::int_fast32_t now_time{ max_time };
	while (mainLoop()) {
		if (++now_time < max_time) continue;
		diagram.init();
		diagram.create(col, 200, 0.3);
		dtl::noiseShoreBool(col, 0.4);
		output(col);
		now_time = 0;
	}
}

//�O�����֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, std::int_fast32_t) {
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(window_map_size_x, window_map_size_y, 32);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMainWindowText("Voronoi");
	VMain();
	return DxLib_End();
}