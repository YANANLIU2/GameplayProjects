#include <vector>
#include <memory>
#include "MyMath.h"
#include "GameState.h"
using std::vector;

// A manager manages all game states and goes to next state when the current state finishes
class Player;
class ObjBase;
class GameState;
class GameStateMachine
{
	// An array of all game states 
	vector<GameState*> game_states_;

	// The current game state which will be updated and rendered
	GameState* current_state_;

	// Instance handle
	HINSTANCE h_instance_;

	// Whether the game is playing or not
	bool is_playing_;

	// Whether the player wins or not 
	bool is_win_;

	// A smart pointer of input class, the game engine has its ownership
	std::unique_ptr<Input> input_;

	// Find a game state by its type
	GameState* get_state_by_type(GameState::EStateType type);

public:
	// Constructor 
	GameStateMachine() : h_instance_(), is_win_(false), current_state_(nullptr), is_playing_(true), input_(std::make_unique<Input>()) {}

	// Destructor
	~GameStateMachine();

	// Initialization
	bool Init(HWND hWindow, HINSTANCE hInstance);

	// Get whether the game is still playing or not
	bool get_is_playing() { return is_playing_; }

	// Set whether the game is still playing or not 
	void set_is_playing(bool isPlaying) { is_playing_ = isPlaying; }
	
	// Get whether the player wins or not
	bool get_is_win();

	// Set whether the player wins or not
	void set_is_win(bool win) { is_win_ = win; }

	// Get input refernce from the game state machine
	Input* get_input() { return input_.get(); }

	// Update the current state, input, etc...
	void Update();
	
	// Render the current state
	void Draw();
	
	// Reset the whole game
	void Reset();

	// State
	void NextState();
};


