#ifndef __BOID_HPP
#define __BOID_HPP

#include <stdlib.h>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

using vec = glm::vec2;

class Boid {
private:
    vec          m_position;
    p6::Rotation m_rotation;
    vec          m_speed;
    vec          m_acceleration;
    vec          m_direction;
    p6::Radius   m_radius;
    p6::Color    m_color;

public:
    // constructors
    Boid(float x, float y, p6::Rotation rotation, p6::Radius radius, p6::Color color);

    // Destructor
    ~Boid();

    void setPos(float posX, float posY);

    inline void setRotation(p6::Rotation rotation) { m_rotation = rotation; }
    inline vec  getPosition() const { return m_position; }
    inline void setPosition(vec position) { m_position = position; }

    [[nodiscard]] inline auto getRotation() const -> p6::Rotation { return m_rotation; }
    inline vec                getSpeed() const { return m_speed; }
    inline vec                getAcceleration() const { return m_acceleration; }
    inline p6::Color          getColor() const { return m_color; }
    void                      update(float deltaTime);
    vec                       separation(const std::vector<Boid>& boids, float separationDistance);
    vec                       alignement(const std::vector<Boid>& boids, float alignementDistance);
    vec                       cohesion(const std::vector<Boid>& boids, float cohesionDistance);
    vec                       seek(const vec target);
    vec                       limit(const vec v, float max);
    void                      draw(p6::Context& ctx);
};

#endif