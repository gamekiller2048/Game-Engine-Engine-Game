#include <math/random.hpp>

namespace mml
{
    namespace rng
    {
        static std::default_random_engine generator;

        int Int(int a, int b)
        {
            std::uniform_int_distribution<int> dist(a, b);
            return dist(generator);
        }

        float Float(float a, float b)
        {
            std::uniform_real_distribution<float> dist(a, b);
            return dist(generator);
        }

        float Random()
        {
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            return dist(generator);
        }

        mml::vec2 Vec2(float a, float b)
        {
            std::uniform_real_distribution<float> dist(a, b);
            return mml::vec2(dist(generator), dist(generator));
        }

        mml::vec3 Vec3(float a, float b)
        {
            std::uniform_real_distribution<float> dist(a, b);
            return mml::vec3(dist(generator), dist(generator), dist(generator));
        }

        mml::vec4 Vec4(float a, float b)
        {
            std::uniform_real_distribution<float> dist(a, b);
            return mml::vec4(dist(generator), dist(generator), dist(generator), dist(generator));
        }

        void _init()
        {
            std::mt19937 rng(generator());
        }
    }
}
