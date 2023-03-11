#include <stdlib.h>
#include <cstddef>
#include <iterator>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Boid.hpp"
#include "doctest/doctest.h"

float Deg2Rad(int deg)
{
    return static_cast<float>(deg) * (p6::PI / static_cast<float>(180));
}

glm::vec2 newPosFromAngle(float centerX, float centerY, int angle, float velocity)
{
    glm::vec2 newPos;

    newPos.x = (velocity * cos(Deg2Rad(angle))) / 2.f + centerX;
    newPos.y = (velocity * sin(Deg2Rad(angle))) / 2.f + centerY;

    return newPos;
}

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available =
            argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto  ctx   = p6::Context{{.title = "Simple-p6-Setup"}};
    auto& myRef = ctx;
    ctx.maximize_window();

    float windowWidth = ctx.aspect_ratio();

    // Create vector of boids
    std::vector<Boid> boids;

    for (int i = 0; i < 2; i++)
    {
        glm::vec2 RandCoord = p6::random::point();
        boids.emplace_back(glm::vec2(RandCoord.x * windowWidth, RandCoord.y), p6::random::number(1, 360), 0.017, p6::Color(1.f, 0.f, 1.f));
    }

    bool isNear = false;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.use_stroke = false;
        ctx.fill       = {0.f, 0.f, 0.f};
        ctx.rectangle(p6::FullScreen{});
        const float treshhold = 0.35f;

        for (Boid& i : boids)
        {
            ctx.fill = {0.f, 1.f, 0.f};
            ctx.circle(p6::Center{i.getXcoord(), i.getYcoord()}, p6::Radius{treshhold});

            i.draw(myRef);

            // create direction
            int direction = p6::random::number(1, 100);

            if (direction <= 20)
            {
                i.setAngle(i.getAngle() + 10);
            }
            else if (direction >= 80)
            {
                i.setAngle(i.getAngle() - 10);
            }

            // New position (make them move in the loop)
            glm::vec2 newPos =
                newPosFromAngle(i.getXcoord(), i.getYcoord(), i.getAngle(), i.getVelocity());
            if (newPos.x > windowWidth)
                newPos.x = -1.f * windowWidth;
            if (newPos.y > 1)
                newPos.y = -1.f;
            if (newPos.x < -windowWidth)
                newPos.x = 1.f * windowWidth;
            if (newPos.y < -1)
                newPos.y = 1.f;
            i.setPos(newPos.x, newPos.y);
        }

        for (size_t j = 0; j < boids.size(); j++)
        {
            if (glm::distance(boids[j].getCenter(), boids[j + 1].getCenter()) < treshhold)
            {
                isNear = true;
            }
            else
            {
                isNear = false;
            }
        }
        std::cout << isNear << std::endl;
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}