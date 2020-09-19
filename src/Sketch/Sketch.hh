#pragma once
#include <raylib.h>

#include <string>
#include <iostream>

class Sketch
{
protected:
	int screenWidth{800};
	int screenHeight{450};
	int fps{60};
	std::string windowName;
	void resetWindow();
	auto MainLoop() -> void;
	virtual void Draw(){};
	virtual void Setup() { std::cout << "h\n"; };
	virtual void Update(){};
	virtual void Unload(){};

public:
	Sketch();
	Sketch(Sketch &&) = default;
	Sketch(const Sketch &) = default;
	Sketch &operator=(Sketch &&) = default;
	Sketch &operator=(const Sketch &) = default;
	~Sketch();

	operator int();

private:
};