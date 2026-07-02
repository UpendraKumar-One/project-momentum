#pragma once

struct _Transform
{
    float f_x, f_y;
    float f_scale_x, f_scale_y;
    float f_rotation;
};

struct _RigidBody
{
    float f_velocity_x, f_velocity_y;
    float f_acceleration_x, f_acceleration_y;

    float f_mass;
    float f_drag;

    bool b_isKinematic;
};

struct _HitBox
{
    float f_width, f_height;
    float f_offsetTransform_x, f_offsetTransform_y;
};