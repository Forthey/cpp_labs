#pragma once
#include <vector>
#include <functional>

#include "Gem.hpp"

using Gems = std::vector<Gem>;
using FieldSize = Point;

class GemsField {
	Gems gems;
	FieldSize fieldSize;
public:
	GemsField(FieldSize const& fieldSize, std::function<GemType(Point)> typeGen);

	Gem& at(int const x, int const y) {
		return gems[y * fieldSize.x + x];
	}
	Gem& at(Point const& pos) {
		return at(pos.x, pos.y);
	}
	Gem const& at(int const x, int const y) const {
		return gems[y * fieldSize.x + x];
	}
	Gems const& getGems() const { return gems; }
	FieldSize const& getFieldSize() const { return fieldSize; }
};

