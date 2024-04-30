#pragma once
#include <array>

enum class GemType {
	RED = 0,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	CYAN,
	NONE,
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
	void setFocus(bool focused_) { focused = focused_; }
	bool getFocus() const { return focused; }
};

