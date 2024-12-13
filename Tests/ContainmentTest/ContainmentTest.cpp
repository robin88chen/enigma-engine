#include "pch.h"
#include "CppUnitTest.h"
#include "Collision/ContainmentBox2.hpp"
#include "Collision/ContainmentBox3.hpp"
#include "Collision/ContainmentSphere2.hpp"
#include "Math/Box2.hpp"
#include "Math/Sphere2.hpp"
#include "Math/Box3.hpp"
#include "Math/Sphere3.hpp"
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
            Point2 center(unif_rand(generator), unif_rand(generator));
            Vector2 axis0(unif_rand(generator), unif_rand(generator));
            axis0.normalizeSelf();
            Vector2 axis1 = axis0.perpendicular();
            float extent0 = positive_rand(generator);
            float extent1 = positive_rand(generator);
            Box2 box0(center, axis0, axis1, extent0, extent1);
            Point2 center1(unif_rand(generator), unif_rand(generator));
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
            Sphere2 sphere0(center, extent0);
            Box2 box_contain_sphere(center, axis0, axis1, extent0, extent0);
            Assert::IsTrue(ContainmentBox2::testBox2EnvelopSphere2(box_contain_sphere, sphere0));
            mergedBox = ContainmentBox2::mergeBoxes(box1, box_contain_sphere);
            Assert::IsTrue(ContainmentBox2::testBox2EnvelopBox2(mergedBox, box1));
            Assert::IsTrue(ContainmentBox2::testBox2EnvelopBox2(mergedBox, box_contain_sphere));
        }
        TEST_METHOD(TestBox3)
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
            Point3 center1(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector3 axis01(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis01.normalizeSelf();
            Vector3 axis11(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis11.normalizeSelf();
            Vector3 axis21 = axis01.cross(axis11);
            axis21.normalizeSelf();
            axis11 = axis21.cross(axis01);
            float extent01 = positive_rand(generator);
            float extent11 = positive_rand(generator);
            float extent21 = positive_rand(generator);
            Box3 box1(center1, axis01, axis11, axis21, extent01, extent11, extent21);
            Box3 mergedBox = ContainmentBox3::mergeBoxes(box0, box1);
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(mergedBox, box0));
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(mergedBox, box1));
            Sphere3 sphere0(center, extent0);
            Box3 box_contain_sphere(center, axis0, axis1, axis2, extent0, extent0, extent0);
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopSphere3(box_contain_sphere, sphere0));
            mergedBox = ContainmentBox3::mergeBoxes(box1, box_contain_sphere);
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(mergedBox, box1));
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(mergedBox, box_contain_sphere));
            std::array<Point3, Box3::VERTICES_COUNT> vertices_array = box1.computeVertices();
            std::vector<Point3> vertices(vertices_array.begin(), vertices_array.end());
            Box3 box2 = ContainmentBox3::computeAlignedBox(vertices);
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(box2, box1));
            Box3 box3 = ContainmentBox3::computeOrientedBox(vertices);
            Assert::IsTrue(ContainmentBox3::testBox3EnvelopBox3(box3, box1));
        }
    };
}
