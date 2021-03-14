#pragma once
#include "Actor.h"

// The class is for providing coins that a player can collect. All collision will be calculated in InGameState. 
class Coin :
    public Actor
{
public:
    // An array of animations for all enemies 
    static vector<AnimationPair> animation_vec_;

    // Construtor 
    Coin(float x, float y);

    // Destructor
    ~Coin() = default;

    // Update
    void Update() override final;

    // Render
    HBITMAP GethBmp() override final;

    BITMAP GetBitmap() override final;
};

