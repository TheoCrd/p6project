#include "Boid.hpp"
#include "glm/fwd.hpp"

// Default constructor
Boid::Boid()
    : m_center(0.f, 0.f), m_angle(0), m_velocity(0), m_color(1.f, 0.f, 0.f) {}

Boid::Boid(glm::vec2 center, int angle, float velocity, p6::Color color)
    : m_center(center), m_angle(angle), m_velocity(velocity), m_color(color) {}

void Boid::setPos(float posX, float posY)
{
    m_center.x = posX;
    m_center.y = posY;
};

void Boid::draw(p6::Context& ctx)
{
    // create a square
    ctx.fill = getColor();
    ctx.equilateral_triangle(p6::Center{getXcoord(), getYcoord()}, p6::Radius{0.09f}, p6::Rotation{p6::Angle(p6::Radians(45))});
}