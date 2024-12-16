#include "pch.h"
#include "CppUnitTest.h"
#include "Collision/IntrLine3Box3.hpp"
#include "Collision/IntrLine3Sphere3.hpp"
#include "Collision/IntrRay3Box3.hpp"
#include "Math/MathGlobal.hpp"
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
            Assert::IsTrue(intrLineBox.find());
            Assert::IsTrue(intrLineBox.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrLineBox.getQuantity() == 2);
            Assert::IsTrue(FloatCompare::isEqual(intrLineBox.getLineT(0), -intrLineBox.getLineT(1)));
            Point3 origin1 = center + (axis0 * extent0 * 0.5f) + (axis1 * extent1 * 0.5f) + (axis2 * extent2 * 0.5f);
            Vector3 direction1 = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            direction1.normalizeSelf();
            Line3 line1(origin1, direction1);
            IntrLine3Box3 intrLineBox1(line1, box0);
            Assert::IsTrue(intrLineBox1.test());
            Assert::IsTrue(intrLineBox1.find());
            Assert::IsTrue(intrLineBox1.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrLineBox1.getQuantity() == 2);
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(box0.contains(intrLineBox1.getPoint(0)));
            Assert::IsTrue(box0.contains(intrLineBox1.getPoint(1)));
        }
        TEST_METHOD(TestLineSphere)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> positive_rand(0.0f, std::nextafter(30.0f, 30.1f));
            Point3 center(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            float radius = positive_rand(generator);
            Sphere3 sphere0(center, radius);
            Vector3 direction(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            direction.normalizeSelf();
            Line3 line0(center, direction);
            IntrLine3Sphere3 intrLineSphere(line0, sphere0);
            Assert::IsTrue(intrLineSphere.test());
            Assert::IsTrue(intrLineSphere.find());
            Assert::IsTrue(intrLineSphere.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrLineSphere.getQuantity() == 2);
            Assert::IsTrue(FloatCompare::isEqual(intrLineSphere.getLineT(0), -intrLineSphere.getLineT(1)));
            Point3 origin1 = center + (direction * radius * 0.5f);
            Vector3 direction1 = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            direction1.normalizeSelf();
            Line3 line1(origin1, direction1);
            IntrLine3Sphere3 intrLineSphere1(line1, sphere0);
            Assert::IsTrue(intrLineSphere1.test());
            Assert::IsTrue(intrLineSphere1.find());
            Assert::IsTrue(intrLineSphere1.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrLineSphere1.getQuantity() == 2);
            //FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(sphere0.contains(intrLineSphere1.getPoint(0)));
            Assert::IsTrue(sphere0.contains(intrLineSphere1.getPoint(1)));
        }
        TEST_METHOD(TestRayBox)
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
            Point3 origin = center + (direction * -60.0f);
            Ray3 ray0(origin, direction);
            IntrRay3Box3 intrRayBox(ray0, box0);
            Assert::IsTrue(intrRayBox.test());
            Assert::IsTrue(intrRayBox.find());
            Assert::IsTrue(intrRayBox.intersectionType() == Intersector::IntersectionType::point);
            Assert::IsTrue(intrRayBox.getQuantity() == 2);
            float center_t = (intrRayBox.getRayT(0) + intrRayBox.getRayT(1)) / 2.0f;
            Assert::IsTrue(center == origin + direction * center_t);
        }
    };
}
