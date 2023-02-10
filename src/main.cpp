#include <cstddef>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

auto main(int argc, char* argv[]) -> int
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    std::vector<glm::vec2> v(100);
    for (size_t i = 0; i < v.size(); ++i)
    {
        v[i] = p6::random::point();
    }

    // Actual app
    auto ctx = p6::Context{{.title = "p6Project"}};
    ctx.maximize_window();

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Black);
        /*ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );*/
        ctx.fill = {1, 0, 0, 0.5};
        for (size_t i = 0; i < 100; ++i)
        {
            ctx.square(p6::Center{v[i]}, p6::Radius{0.1f});
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}