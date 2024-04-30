#pragma once
#include <array>

enum class GemType {
	RED = 0,
	GREEN,
	BLUE,
	YELLOW,
	TYPE_CNT
};

struct Point {
	int x;
	int y;
};


class Gem {
	GemType type;
	bool focused = false;
public:
	explicit Gem(GemType type) : type(type) {}
	Gem(Gem const& gem) : type(gem.type), focused(gem.focused) {}
	GemType const& getType() const { return type; }
	void setFocus(bool focused) { this->focused = focused; }
	bool getFocus() const { return focused; }
};

