#include "SimpleVoronoiIsland.hpp"
#include "DungeonTemplateOutput.hpp"
#include "DungeonNoise.hpp"
#include <array>
#include <bitset>

int main() {
	std::array<std::bitset<96>, 64> dungeon{ {} };
	dtl::SimpleVoronoiIsland<bool> dungeon_creater(dungeon, 100, 0.5);
	dtl::noiseShoreBool(dungeon, 0.5);
	dtl::dungeonStringOutputBool(dungeon, "*", " ");
}