#pragma once

class Game
{
public:
	Game();
	~Game();

	void run();


private:
	void init();
	void processInput();
	void update();
	void draw();

	bool running = false;
};

