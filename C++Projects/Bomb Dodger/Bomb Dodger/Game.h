#include "Player.h"
#include "Bomb.h"
#include <iostream>
#include <vector>

class Player;
class Bomb;

constexpr int kBombCount = 5;

class Game
{
private:
	bool m_isPlaying;

	ObjBase* m_player;
	std::vector<ObjBase*> m_BombVec;
	bool m_win;
	float m_score;

	HWND m_hWindow;

	// Disable Triangle of Evil
	Game(const Game& game) = delete;
	Game();
	~Game();

	
public:

	static Game& Get();
	bool Init(HWND hWindow, HINSTANCE hInstance);
	void Update();
	void Draw();
	void Cleanup();
	void Reset();
	void GoRight(bool right);
	void Collision();
	bool CollideWithPlayer(ObjBase* Bomb, ObjBase* player);
	// Accessors
	bool IsPlaying() const { return m_isPlaying; }
	void StopMoving();
	// Mutators
	void SetIsPlaying(bool isPlaying) { m_isPlaying = isPlaying; }
	void BombChange();

};

