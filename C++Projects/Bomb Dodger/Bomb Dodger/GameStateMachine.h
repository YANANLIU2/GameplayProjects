#include <vector>
#include "GameState.h"
#include "Input.h"

class Player;
class ObjBase;
class GameState;

class GameStateMachine
{
private:
	std::vector<GameState*> game_states_;
	GameState* current_state_;
	HINSTANCE h_instance_;
	bool is_playing_;
	bool is_win_;

	void LoadaImage(HBITMAP& hBmp, BITMAP& Bitmap, int IDB);
	GameState* GetStateByType(GameState::EStateType type);

public:
	// Constructor & Destructor
	GameStateMachine()
		: h_instance_()
		, is_win_(false)
		, current_state_(nullptr)
		, is_playing_(true)
	{
	}

	~GameStateMachine();

	// Getters & Setters
	bool get_is_playing() { return is_playing_; }
	void set_is_playing(bool isPlaying) { is_playing_ = isPlaying; }
	bool get_is_win();
	void set_is_win(bool win) { is_win_ = win; }
	
	// Main Loop
	bool Init(HWND hWindow, HINSTANCE hInstance);
	void Update();
	void Draw();

	// State
	void NextState();
	void GetInput(Input::InputValue input);
};


