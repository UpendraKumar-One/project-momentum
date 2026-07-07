#pragma once

class Registry;

class PhysicsSystem
{
public:
    PhysicsSystem(float gravity);
    void update(Registry& reg, float dt);

private:
    float GRAVITY;
};