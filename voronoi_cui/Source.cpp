#include "SimpleVoronoiIsland.hpp"
#include "DungeonTemplateOutput.hpp"
#include <array>
#include <bitset>

int main() {
	std::array<std::bitset<96>, 64> col{ {} };
	dtl::SimpleVoronoiIsland<bool> diagram(col, 100, 0.5);
	dtl::noiseShoreBool(col, 0.5);
	dtl::outputBoolBitSet(col, "*", " ");
}