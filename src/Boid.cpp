#include "Boid.hpp"
#include <cmath>
#include <cstddef>
#include <vector>
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"

Boid::Boid(float x, float y, p6::Rotation rotation, p6::Radius radius, p6::Color color)
    : m_position(x, y), m_rotation(rotation), m_speed(0.f), m_acceleration(0.f), m_radius(radius), m_color(color)
{
    m_direction = glm::vec3(p6::rotated_by(rotation, vec(1., 0.)), 0.);
}

void Boid::update(float deltaTime)
{
    m_speed += m_acceleration * deltaTime;
    m_position += m_speed * deltaTime;
}

vec Boid::separation(const std::vector<Boid>& boids, float separationDistance)
{
    vec    steer(0.f);
    size_t count = 0;
    for (const auto& other : boids)
    {
        if (&other != this)
        {
            float distance = glm::distance(this->m_position, other.m_position);
            if (distance > 0 && distance < separationDistance)
            {
                // relative position
                vec difference = this->m_position - other.m_position;
                difference /= distance;
                steer += difference;
                count++;
            }
        }
    }
    if (count > 0)
    {
        steer /= static_cast<float>(count);
        steer = glm::normalize(steer);
    }
    return steer;
}

vec Boid::alignement(const std::vector<Boid>& boids, float alignementDistance)
{
    vec    sum(0.f);
    size_t count = 0;
    for (const auto& other : boids)
    {
        if (&other != this)
        {
            float distance = glm::distance(this->m_position, other.m_position);
            if (distance > 0 && distance < alignementDistance)
            {
                sum += other.m_speed;
                count++;
            }
        }
    }
    if (count > 0)
    {
        sum /= static_cast<float>(count);
        sum = glm::normalize(sum);
    }
    return sum;
}

vec Boid::cohesion(const std::vector<Boid>& boids, float cohesionDistance)
{
    vec    centering(0.f);
    size_t count = 0;
    for (const auto& other : boids)
    {
        if (&other != this)
        {
            float distance = glm::distance(this->m_position, other.m_position);
            if (distance > 0 && distance < cohesionDistance)
            {
                centering += other.m_position;
                count++;
            }
        }
    }
    if (count > 0)
    {
        centering /= static_cast<float>(count);
        return seek(centering);
    }
    return centering;
}

// boid searching around us
vec Boid::seek(const vec target)
{
    vec desired = target - this->m_position;
    desired     = glm::normalize(desired);
    desired *= 5.0f; // max speed
    vec steer = desired - this->m_speed;
    steer     = limit(steer, 0.5f);
    return steer;
}

// a limiter (for speed as an example)
vec Boid::limit(const vec v, float max)
{
    float higher = std::sqrt(v.x * v.x + v.y * v.y);
    if (higher > max)
    {
        return glm::normalize(v) * max;
    }
    return v;
}

void Boid::draw(p6::Context& ctx)
{
    ctx.fill = getColor();
    ctx.equilateral_triangle(
        p6::Center{m_position},
        m_radius,
        p6::Rotation{p6::Angle(vec(m_direction))}
    );
}