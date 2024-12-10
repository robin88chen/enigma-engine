#include "pch.h"
#include "CppUnitTest.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/MathGlobal.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Math;

namespace MathLibTests
{
    TEST_CLASS(MathVectorTests)
    {
    public:

        TEST_METHOD(Vector2Test)
        {
            Assert::IsTrue(Vector2(0.0f, 1.0f) == Vector2::UNIT_Y);
            Assert::IsTrue(Vector2(1.0f, 0.0f) == Vector2::UNIT_X);
            Assert::IsTrue(Vector2(0.0f, 0.0f) == Vector2::ZERO);

            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-1000.0f, std::nextafter(1000.0f, 1001.0f));
            Vector2 vec21(unif_rand(generator), unif_rand(generator));
            Vector2 vec22(unif_rand(generator), unif_rand(generator));
            float* ar21 = (float*)vec21;
            float* ar22 = (float*)vec22;
            Assert::IsTrue(FloatCompare::isEqual(ar21[0], vec21.x()));
            Assert::IsTrue(FloatCompare::isEqual(ar22[1], vec22.y()));

            //Vector2 vec23 = Vector2(ar21);
            //Assert::IsTrue(vec21 == vec23);
            Vector2 vec24 = Vector2(ar21[0] + ar22[0], ar21[1] + ar22[1]);
            Assert::IsTrue(vec24 == (vec21 + vec22));
            Vector2 vec25 = Vector2(ar21[0] - ar22[0], ar21[1] - ar22[1]);
            Assert::IsTrue(vec25 == (vec21 - vec22));
            Vector2 vec26 = Vector2(-ar22[0], -ar22[1]);
            Assert::IsTrue(vec26 == -vec22);
            Vector2 vec27 = Vector2(2.0f * ar21[0] - ar22[0] / 3.0f, 2.0f * ar21[1] - ar22[1] / 3.0f);
            Assert::IsTrue(vec27 == (2.0f * vec21 - vec22 / 3.0f));
            Vector2 vec28 = vec21;
            vec28 += vec22;
            Assert::IsTrue(vec28 == vec24);
            float l2 = vec21.dot(vec21);
            Assert::IsTrue(FloatCompare::isEqual(sqrt(l2), vec21.length()));
            Assert::IsTrue(FloatCompare::isEqual(vec21.squaredLength(), l2));
            Assert::IsTrue(FloatCompare::isEqual(vec21.length() * vec21.length(), l2));
            float ll02 = vec21.length();
            Vector2 vec29 = vec21.normalize();
            Assert::IsTrue(vec29 == vec21 / ll02);
            Vector2 vec211 = vec21.perpendicular();
            Assert::IsTrue(FloatCompare::isEqual(vec211.dot(vec21), 0.0f));
            Vector2 vec213 = vec21.unitPerpendicular();
            Vector2 vec214 = vec211.normalize();
            Assert::IsTrue(vec213 == vec214);
            Assert::IsTrue(FloatCompare::isEqual(vec21.dotPerpendicular(vec22), vec21.dot(vec22.perpendicular())));
        }

        TEST_METHOD(Vector3Test)
        {
            Assert::IsTrue(Vector3(0.0f, 1.0f, 0.0f) == Vector3::UNIT_Y);
            Assert::IsTrue(Vector3(1.0f, 0.0f, 0.0f) == Vector3::UNIT_X);
            Assert::IsTrue(Vector3(0.0f, 0.0f, 1.0f) == Vector3::UNIT_Z);
            Assert::IsTrue(Vector3(0.0f, 0.0f, 0.0f) == Vector3::ZERO);

            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-1000.0f, std::nextafter(1000.0f, 1001.0f));

            Vector3 vec31 = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector3 vec32 = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            //Assert::IsTrue(FloatCompare::isEqual(vec31.x,vec31.X()));
            //Assert::IsTrue(FloatCompare::isEqual(vec32.y,vec32.Y()));
            float* ar31 = (float*)vec31;
            float* ar32 = (float*)vec32;
            Assert::IsTrue(FloatCompare::isEqual(ar31[2], vec31.z()));
            Assert::IsTrue(FloatCompare::isEqual(ar32[1], vec32.y()));
            //Vector3 vec33 = Vector3(ar31);
            //Assert::IsTrue(vec31 == vec33);
            Vector3 vec34 = Vector3(ar31[0] + ar32[0], ar31[1] + ar32[1], ar31[2] + ar32[2]);
            Assert::IsTrue(vec34 == (vec31 + vec32));
            Vector3 vec35 = Vector3(ar31[0] - ar32[0], ar31[1] - ar32[1], ar31[2] - ar32[2]);
            Assert::IsTrue(vec35 == (vec31 - vec32));
            Vector3 vec36 = Vector3(-ar32[0], -ar32[1], -ar32[2]);
            Assert::IsTrue(vec36 == -vec32);
            Vector3 vec37 = Vector3(2.0f * ar31[0] - ar32[0] / 3.0f, 2.0f * ar31[1] - ar32[1] / 3.0f, 2.0f * ar31[2] - ar32[2] / 3.0f);
            Assert::IsTrue(vec37 == (2.0f * vec31 - vec32 / 3.0f));
            Vector3 vec38 = vec31;
            vec38 += vec32;
            Assert::IsTrue(vec38 == vec34);
            float l3 = vec31.dot(vec31);
            Assert::IsTrue(FloatCompare::isEqual(vec31.squaredLength(), l3));
            Assert::IsTrue(FloatCompare::isEqual(vec31.length() * vec31.length(), l3));
            float ll3 = vec31.length();
            Vector3 vec39 = vec31.normalize();
            Assert::IsTrue(vec39 == vec31 / ll3);
            Vector3 vec311 = vec31.cross(vec32);
            Assert::IsTrue(FloatCompare::isEqual(vec311.normalize().dot(vec31.normalize()), 0.0f));
            Assert::IsTrue(FloatCompare::isEqual(vec311.normalize().dot(vec32.normalize()), 0.0f));
            //Assert::IsTrue(FloatCompare::isEqual(vec311.Dot(vec31), 0.0f));  // 浮點數乘除後的誤差會放大，一旦維度很大，就注定會失敗
            //Assert::IsTrue(FloatCompare::isEqual(vec311.Dot(vec32), 0.0f));
            Vector3 vec312 = vec32.cross(vec31);
            Assert::IsTrue(vec312 == -vec311);
            Vector3 vec313 = vec31.unitCross(vec32);
            Vector3 vec314 = vec311.normalize();
            Assert::IsTrue(vec313 == vec314);

        }

        TEST_METHOD(Vector4Test)
        {
            Assert::IsTrue(Vector4(0.0f, 1.0f, 0.0f, 0.0f) == Vector4::UNIT_Y);
            Assert::IsTrue(Vector4(1.0f, 0.0f, 0.0f, 0.0f) == Vector4::UNIT_X);
            Assert::IsTrue(Vector4(0.0f, 0.0f, 1.0f, 0.0f) == Vector4::UNIT_Z);
            Assert::IsTrue(Vector4(0.0f, 0.0f, 0.0f, 1.0f) == Vector4::UNIT_W);
            Assert::IsTrue(Vector4(0.0f, 0.0f, 0.0f, 0.0f) == Vector4::ZERO);

            //Assert::IsTrue(Vector4(-0.1f,-0.2f,-1.0f,-1.0f)<=Vector4::ZERO);
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-1000.0f, std::nextafter(1000.0f, 1001.0f));

            Vector4 vec1 = Vector4(unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector4 vec2 = Vector4(unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator));
            //Assert::IsTrue(FloatCompare::isEqual(vec1.x,vec1.X()));
            //Assert::IsTrue(FloatCompare::isEqual(vec2.y,vec2.Y()));
            float* ar1 = (float*)vec1;
            float* ar2 = (float*)vec2;
            Assert::IsTrue(FloatCompare::isEqual(ar1[2], vec1.z()));
            Assert::IsTrue(FloatCompare::isEqual(ar2[3], vec2.w()));
            //Vector4 vec3 = Vector4(ar1);
            //Assert::IsTrue(vec1 == vec3);
            Vector4 vec4 = Vector4(ar1[0] + ar2[0], ar1[1] + ar2[1], ar1[2] + ar2[2], ar1[3] + ar2[3]);
            Assert::IsTrue(vec4 == (vec1 + vec2));
            Vector4 vec5 = Vector4(ar1[0] - ar2[0], ar1[1] - ar2[1], ar1[2] - ar2[2], ar1[3] - ar2[3]);
            Assert::IsTrue(vec5 == (vec1 - vec2));
            Vector4 vec6 = Vector4(-ar2[0], -ar2[1], -ar2[2], -ar2[3]);
            Assert::IsTrue(vec6 == -vec2);
            Vector4 vec7 = Vector4(2.0f * ar1[0] - ar2[0] / 3.0f, 2.0f * ar1[1] - ar2[1] / 3.0f, 2.0f * ar1[2] - ar2[2] / 3.0f, 2.0f * ar1[3] - ar2[3] / 3.0f);
            Assert::IsTrue(vec7 == (2.0f * vec1 - vec2 / 3.0f));
            Vector4 vec8 = vec1;
            vec8 += vec2;
            Assert::IsTrue(vec8 == vec4);
            float l = vec1.dot(vec1);
            Assert::IsTrue(FloatCompare::isEqual(vec1.squaredLength(), l));
            Assert::IsTrue(FloatCompare::isEqual(vec1.length() * vec1.length(), l));
            float ll = vec1.length();
            Vector4 vec9 = vec1.normalize();
            Assert::IsTrue(vec9 == vec1 / ll);
        }
    };
}
