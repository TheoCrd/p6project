#ifndef __BOID_HPP
#define __BOID_HPP

#include <stdlib.h>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid {
private:
    glm::vec2 m_center;
    int       m_angle;
    float     m_velocity;
    p6::Color m_color;

public:
    // constructors
    Boid();
    Boid(glm::vec2 center, int angle, float velocity, p6::Color color);

    void setPos(float posX, float posY);

    inline void      setAngle(int angle) { m_angle = angle; }
    inline float     getXcoord() const { return m_center.x; }
    inline float     getYcoord() const { return m_center.y; }
    inline glm::vec2 getCenter() const { return m_center; }

    inline int       getAngle() const { return m_angle; }
    inline float     getVelocity() const { return m_velocity; }
    inline p6::Color getColor() const { return m_color; }
    void             draw(p6::Context& ctx);
};

#endif