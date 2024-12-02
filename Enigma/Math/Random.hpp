/*********************************************************************
 * \file   Random.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <random>
#include <memory>

namespace Math
{
    class UniformDoubleDistribution : public std::uniform_real_distribution<double>
    {
    public:
        UniformDoubleDistribution(double min_a, double max_a, const std::shared_ptr<std::default_random_engine>& generator)
            : std::uniform_real_distribution<double>(min_a, max_a), m_generator(generator) {}

        double operator()()
        {
            return std::uniform_real_distribution<double>::operator()(*m_generator);
        }
    protected:
        std::shared_ptr<std::default_random_engine> m_generator;
    };

    class UniformFloatDistribution : public std::uniform_real_distribution<float>
    {
    public:
        UniformFloatDistribution(float min_a, float max_a, const std::shared_ptr<std::default_random_engine>& generator)
            : std::uniform_real_distribution<float>(min_a, max_a), m_generator(generator) {}

        float operator()()
        {
            return std::uniform_real_distribution<float>::operator()(*m_generator);
        }
    protected:
        std::shared_ptr<std::default_random_engine> m_generator;
    };

    class UniformIntDistribution : public std::uniform_int_distribution<int>
    {
    public:
        UniformIntDistribution(int min_a, int max_a, const std::shared_ptr<std::default_random_engine>& generator)
            : std::uniform_int_distribution<int>(min_a, max_a), m_generator(generator) {}

        int operator()()
        {
            return std::uniform_int_distribution<int>::operator()(*m_generator);
        }
    protected:
        std::shared_ptr<std::default_random_engine> m_generator;
    };

    class Random
    {
    public:
        /** has initial seeded */
        static bool hasSeeded();
        /** Random Seed */
        static void randomSeed();
        /** Generate a random number in [0,1).  */
        static double unitRandom();

        /** Generate a random number in [-1,1). */
        static double symmetricRandom();

        /** Generate a random number in [min,max).  */
        static UniformDoubleDistribution intervalDistribution(double min_a, double max_a);
        /** Generate a random number in [min,max).  */
        static UniformFloatDistribution intervalDistribution(float min_a, float max_a);
        /** Generate a random integer (singed) in [min,max). */
        static UniformIntDistribution intervalDistribution(int min_a, int max_a);

    private:
        static bool m_hasSeeded;
        static std::random_device m_randomSeed;
        static std::shared_ptr<std::default_random_engine> m_generator;
        static std::uniform_real_distribution<double> m_unitRand;
        static std::uniform_real_distribution<double> m_symmetricRand;
    };
}

#endif // RANDOM_HPP
