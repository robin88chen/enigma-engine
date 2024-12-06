#include "pch.h"
#include "CppUnitTest.h"
#include "Math/ColorRGB.hpp"
#include "Math/ColorRGBA.hpp"
#include "Math/MathGlobal.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Math;

namespace MathLibTests
{
    TEST_CLASS(MathColorTests)
    {
    public:

        TEST_METHOD(ColorRGBTest)
        {
            Assert::IsTrue(ColorRGB(0.0f, 0.0f, 0.0f) == ColorRGB::BLACK);
            Assert::IsTrue(ColorRGB(1.0f, 1.0f, 1.0f) == ColorRGB::WHITE);
            Assert::IsTrue(ColorRGB(0.0f, 0.0f, 0.0f) == ColorRGB::ZERO);

            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(0.0f, std::nextafter(2.0f, 2.1f));
            float r = unif_rand(generator);
            float g = unif_rand(generator);
            float b = unif_rand(generator);
            ColorRGB c1(r, g, b);
            Assert::IsTrue(FloatCompare::isEqual(c1.r(), r));
            Assert::IsTrue(FloatCompare::isEqual(c1.g(), g));
            Assert::IsTrue(FloatCompare::isEqual(c1.b(), b));
            Assert::IsTrue(FloatCompare::isEqual(c1[0], r));
            Assert::IsTrue(FloatCompare::isEqual(c1[2], b));
            Assert::IsTrue(FloatCompare::isEqual(((const float*)c1)[1], g));

            ColorRGB c2 = c1;
            //Assert::IsTrue(c1.rgb() == c2.rgb());
            Assert::IsTrue(c2 == c1);

            std::array<float, 3> rgbs;
            rgbs[0] = unif_rand(generator);
            rgbs[1] = unif_rand(generator);
            rgbs[2] = unif_rand(generator);
            ColorRGB c3(rgbs);
            ColorRGB c4 = c2 + c3;
            Assert::IsTrue(FloatCompare::isEqual(c4.r(), r + rgbs[0]));
            ColorRGB c5 = c4 - c3;
            Assert::IsTrue(FloatCompare::isEqual(c5.g(), g));
            //Assert::IsTrue(FloatCompare::isEqual(c5.g(), g - rgbs[1]));
            ColorRGB c6 = c2 * c3;
            Assert::IsTrue(FloatCompare::isEqual(c6.b(), b * rgbs[2]));
            ColorRGB c7(c3);
            c7 += c2;
            Assert::IsTrue(FloatCompare::isEqual(c7.r(), r + rgbs[0]));
            Assert::IsTrue(FloatCompare::isEqual(c7.g(), c4.g()));
            ColorRGB c8(c4);
            c8 -= c3;
            Assert::IsTrue(FloatCompare::isEqual(c8.r(), r));
            Assert::IsTrue(FloatCompare::isEqual(c8.b(), c5.b()));
            ColorRGB c9(c3);
            c9 *= c2;
            Assert::IsTrue(FloatCompare::isEqual(c9.r(), r * rgbs[0]));
            Assert::IsTrue(FloatCompare::isEqual(c9.g(), c6.g()));
            ColorRGB c10 = 2.0f * c3;
            Assert::IsTrue(FloatCompare::isEqual(c10.r(), 2.0f * rgbs[0]));
            ColorRGB c11(c3);
            c11 *= 2.0f;
            Assert::IsTrue(FloatCompare::isEqual(c11.g(), 2.0f * rgbs[1]));

            ColorRGB c12 = c11.clamp();
            Assert::IsTrue((c12.r() <= 1.0f) && (c12.r() >= 0.0f));
            Assert::IsTrue((c12.g() <= 1.0f) && (c12.g() >= 0.0f));
            Assert::IsTrue((c12.b() <= 1.0f) && (c12.b() >= 0.0f));

            unsigned c12_rgb = c12.rgb();
            ColorRGB rgb_c12 = ColorRGB(c12_rgb);
            Assert::IsTrue(c12.rgb() == rgb_c12.rgb());

            ColorRGB c13(r + 2.0f, g, b);
            ColorRGB c14 = c13.scaleByMax();
            Assert::IsTrue(FloatCompare::isEqual(c14.r(), 1.0f));
            Assert::IsTrue(FloatCompare::isEqual(c14.g(), g / (r + 2.0f)));
        }
        TEST_METHOD(ColorRGBATest)
        {
            Assert::IsTrue(ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f) == ColorRGBA::BLACK);
            Assert::IsTrue(ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f) == ColorRGBA::WHITE);
            Assert::IsTrue(ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f) == ColorRGBA::ZERO);

            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(0.0f, std::nextafter(2.0f, 2.1f));
            float r = unif_rand(generator);
            float g = unif_rand(generator);
            float b = unif_rand(generator);
            float a = unif_rand(generator);
            ColorRGBA c1(r, g, b, a);
            Assert::IsTrue(FloatCompare::isEqual(c1.r(), r));
            Assert::IsTrue(FloatCompare::isEqual(c1.g(), g));
            Assert::IsTrue(FloatCompare::isEqual(c1.b(), b));
            Assert::IsTrue(FloatCompare::isEqual(c1.a(), a));
            Assert::IsTrue(FloatCompare::isEqual(c1[0], r));
            Assert::IsTrue(FloatCompare::isEqual(c1[2], b));
            Assert::IsTrue(FloatCompare::isEqual(((const float*)c1)[3], a));

            ColorRGBA c2 = c1;
            //Assert::IsTrue(c1.argb() == c2.argb());
            Assert::IsTrue(c2 == c1);

            std::array<float, 4> rgbs;
            rgbs[0] = unif_rand(generator);
            rgbs[1] = unif_rand(generator);
            rgbs[2] = unif_rand(generator);
            rgbs[3] = unif_rand(generator);
            ColorRGBA c3(rgbs);
            ColorRGBA c4 = c2 + c3;
            Assert::IsTrue(FloatCompare::isEqual(c4.r(), r + rgbs[0]));
            ColorRGBA c5 = c4 - c3;
            Assert::IsTrue(FloatCompare::isEqual(c5.g(), g));
            ColorRGBA c6 = c2 * c3;
            Assert::IsTrue(FloatCompare::isEqual(c6.a(), a * rgbs[3]));
            ColorRGBA c7(c3);
            c7 += c2;
            Assert::IsTrue(FloatCompare::isEqual(c7.r(), r + rgbs[0]));
            Assert::IsTrue(FloatCompare::isEqual(c7.g(), c4.g()));
            ColorRGBA c8(c4);
            c8 -= c3;
            Assert::IsTrue(FloatCompare::isEqual(c8.r(), r));
            Assert::IsTrue(FloatCompare::isEqual(c8.a(), c5.a()));
            ColorRGBA c9(c3);
            c9 *= c2;
            Assert::IsTrue(FloatCompare::isEqual(c9.a(), a * rgbs[3]));
            Assert::IsTrue(FloatCompare::isEqual(c9.g(), c6.g()));
            ColorRGBA c10 = 2.0f * c3;
            Assert::IsTrue(FloatCompare::isEqual(c10.r(), 2.0f * rgbs[0]));
            ColorRGBA c11(c3);
            c11 *= 2.0f;
            Assert::IsTrue(FloatCompare::isEqual(c11.b(), 2.0f * rgbs[2]));

            ColorRGBA c12 = c11.clamp();
            Assert::IsTrue((c12.r() <= 1.0f) && (c12.r() >= 0.0f));
            Assert::IsTrue((c12.g() <= 1.0f) && (c12.g() >= 0.0f));
            Assert::IsTrue((c12.b() <= 1.0f) && (c12.b() >= 0.0f));
            Assert::IsTrue((c12.a() <= 1.0f) && (c12.a() >= 0.0f));

            unsigned c12_argb = c12.argb();
            ColorRGBA argb_c12 = ColorRGBA(c12_argb & 0xffffff, (std::byte)(c12_argb >> 24));
            Assert::IsTrue(c12.argb() == argb_c12.argb());
            unsigned c12_rgba = c12.rgba();
            Assert::IsTrue(c12.rgba() == argb_c12.rgba());
            Assert::IsTrue((c12_rgba >> 8) == (c12.argb() & 0xffffff));
            ColorRGBA c13(r + 2.0f, g, b, a);
            ColorRGBA c14 = c13.scaleByMax();
            Assert::IsTrue(FloatCompare::isEqual(c14.r(), 1.0f));
            Assert::IsTrue(FloatCompare::isEqual(c14.g(), g / (r + 2.0f)));
        }
    };
}