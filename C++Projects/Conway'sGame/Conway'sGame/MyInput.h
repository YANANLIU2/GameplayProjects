#pragma once
#include "MyVector2.h";

//  The class is for recording player input and providing the values to other objects
class MyInput
{
    // The current position of the player's cursor
    MyVector2<float> mouse_pos_;

    // Whether the player clicked the mouse this frame or not
    bool is_click_;

    // Whether the player dragged the mouse this frame or not
    bool is_drag_;

    // Constructor
    MyInput():mouse_pos_(), is_click_(false), is_drag_(false) {}

public:
    // Singleton Pattern
    static MyInput& get_instance()
    {
        static MyInput instance_;
        return instance_;
    }

    MyInput(MyInput const&) = delete;

    void operator=(MyInput const&) = delete;
	
    // Update 
    inline void Update() { is_click_ = false; }
    
    // Reset
    inline void Reset() { mouse_pos_ = { 0,0 }; is_click_ = false; is_drag_ = false; }

    // Getters & Setters
    inline MyVector2<float> get_mouse_pos() const { return mouse_pos_; }

    // Getters & Setters
    inline void set_mouse_pos(MyVector2<float> pos) { mouse_pos_ = pos; }

    inline bool get_is_click() const { return is_click_; }

    inline bool get_is_drag() const { return is_drag_; }

    void set_is_click(bool value);
                                 
    void set_is_drag(bool value);

	// Destructor
	~MyInput() = default;
};