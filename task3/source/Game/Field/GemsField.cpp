#include "GemsField.hpp"

#include <algorithm>


GemsField::GemsField(FieldSize const& fieldSize, std::function<GemType(Point)> typeGen) : fieldSize(fieldSize) {
	int gemsCnt = fieldSize.x * fieldSize.y;
	int x = 0, y = 0;
	for (int i = 0; i < gemsCnt; i++) {
		gems.push_back(Gem(typeGen({x, y})));
		x = (x + 1) % fieldSize.x;
		if (x == 0) {
			y++;
		}
	}
}

