#pragma once

enum class PlayerState
{
    IDLE,
    SPRINT,
    AIRBORNE
};

struct _Player
{
    float f_moveSpeed;
    float f_jumpForce;

    PlayerState CurrentState;
};