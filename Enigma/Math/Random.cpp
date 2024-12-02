#include "Random.hpp"
#include <cassert>

using namespace Math;

bool Random::m_hasSeeded = false;
std::random_device Random::m_randomSeed;
std::shared_ptr<std::default_random_engine> Random::m_generator;
std::uniform_real_distribution<double> Random::m_unitRand(0.0, 1.0);
std::uniform_real_distribution<double> Random::m_symmetricRand(-1.0, 1.0);

bool Random::hasSeeded()
{
    return m_hasSeeded;
}

void Random::randomSeed()
{
    m_generator = std::make_shared<std::default_random_engine>(m_randomSeed());
    m_hasSeeded = true;
}

double Random::unitRandom()
{
    assert(m_generator);
    return m_unitRand(*m_generator);
}

double Random::symmetricRandom()
{
    assert(m_generator);
    return m_symmetricRand(*m_generator);
}

UniformDoubleDistribution Random::intervalDistribution(double min_a, double max_a)
{
    assert(m_generator);
    return { min_a, max_a, m_generator };
}

UniformFloatDistribution Random::intervalDistribution(float min_a, float max_a)
{
    assert(m_generator);
    return { min_a, max_a, m_generator };
}

UniformIntDistribution Random::intervalDistribution(int min_a, int max_a)
{
    assert(m_generator);
    return { min_a, max_a, m_generator };
}

