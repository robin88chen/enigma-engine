#include "pch.h"
#include "CppUnitTest.h"
#include "Collision/IntrLine3Box3.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Math;
using namespace Collision;

namespace IntersectionTests
{
    TEST_CLASS(IntersectionTests)
    {
    public:

        TEST_METHOD(TestLineBox)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> positive_rand(0.0f, std::nextafter(30.0f, 30.1f));
            Point3 center(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector3 axis0(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis0.normalizeSelf();
            Vector3 axis1(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis1.normalizeSelf();
            Vector3 axis2 = axis0.cross(axis1);
            axis2.normalizeSelf();
            axis1 = axis2.cross(axis0);
            float extent0 = positive_rand(generator);
            float extent1 = positive_rand(generator);
            float extent2 = positive_rand(generator);
            Box3 box0(center, axis0, axis1, axis2, extent0, extent1, extent2);
            Vector3 direction(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            direction.normalizeSelf();
            Line3 line0(center, direction);
            IntrLine3Box3 intrLineBox(line0, box0);
            Assert::IsTrue(intrLineBox.test());
            intrLineBox.find();
            Assert::IsTrue(intrLineBox.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrLineBox.getQuantity() == 2);
        }
    };
}
