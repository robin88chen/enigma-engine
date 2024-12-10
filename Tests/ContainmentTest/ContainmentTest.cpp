#include "pch.h"
#include "CppUnitTest.h"
#include "Collision/ContainmentBox2.hpp"
#include "Math/Box2.hpp"
#include "Math/MathGlobal.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Math;
using namespace Collision;

namespace ContainmentTest
{
    TEST_CLASS(ContainmentTest)
    {
    public:
        TEST_METHOD(TestBox2)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> positive_rand(0.0f, std::nextafter(30.0f, 30.1f));
            Vector2 center(unif_rand(generator), unif_rand(generator));
            Vector2 axis0(unif_rand(generator), unif_rand(generator));
            axis0.normalizeSelf();
            Vector2 axis1 = axis0.perpendicular();
            float extent0 = positive_rand(generator);
            float extent1 = positive_rand(generator);
            Box2 box0(center, axis0, axis1, extent0, extent1);
            Vector2 center1(unif_rand(generator), unif_rand(generator));
            Vector2 axis01(unif_rand(generator), unif_rand(generator));
            axis01.normalizeSelf();
            Vector2 axis11 = axis01.perpendicular();
            float extent01 = positive_rand(generator);
            float extent11 = positive_rand(generator);
            Box2 box1(center1, axis01, axis11, extent01, extent11);
            Box2 mergedBox = ContainmentBox2::mergeBoxes(box0, box1);
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(ContainmentBox2::testBox2EnvelopBox2(mergedBox, box0));
            Assert::IsTrue(ContainmentBox2::testBox2EnvelopBox2(mergedBox, box1));
        }
    };
}
