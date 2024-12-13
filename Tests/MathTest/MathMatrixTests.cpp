#include "pch.h"
#include "CppUnitTest.h"
#include "Math/MathGlobal.hpp"
#include "Math/Matrix2.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Radian.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Point3.hpp"
#include "Math/EulerAngles.hpp"
#include "Math/EulerRotations.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Math;

namespace MathLibTests
{
    TEST_CLASS(MathMatrixTests)
    {
    public:

        TEST_METHOD(Matrix2Test)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> pi_rand(-Constants::PI, Constants::PI);
            Matrix2 mx1 = Matrix2::IDENTITY;
            Assert::IsTrue(mx1 == Matrix2::IDENTITY);
            Matrix2 mx2 = Matrix2();
            Assert::IsTrue(mx2 == Matrix2::ZERO);
            Radian angle = Radian(pi_rand(generator));
            //Matrix2 mxa(angle);
            mx1 = Matrix2::fromAngle(angle);
            //Assert::IsTrue(mx1 == mxa);
            Radian angle2 = mx1.rotationAngle();
            Assert::IsTrue(angle == angle2);
            Matrix2 mx3 = Matrix2::makeIdentity();
            Assert::IsTrue(mx3 == Matrix2::IDENTITY);
            mx3 = Matrix2::makeZero();
            Assert::IsTrue(mx3 == Matrix2::ZERO);
            float m00 = unif_rand(generator);
            float m11 = unif_rand(generator);
            mx3 = Matrix2::makeDiagonal(m00, m11);
            Matrix2 mx4 = Matrix2(m00, 0.0f, 0.0f, m11);
            Assert::IsTrue(mx3 == mx4);
            std::array<float, 4> mrc;
            mrc[0] = unif_rand(generator); mrc[1] = unif_rand(generator);
            mrc[2] = unif_rand(generator); mrc[3] = unif_rand(generator);
            Matrix2 mx5 = Matrix2(mrc[0], mrc[1], mrc[2], mrc[3]);
            Matrix2 mx6 = Matrix2(mrc);
            Assert::IsTrue(mx5 == mx6);
            Assert::IsTrue(FloatCompare::isEqual(mx5[0][0], mrc[0]));
            //Assert::IsTrue(FloatCompare::isEqual(mx5.m_21,mrc[2]));
            Assert::IsTrue(FloatCompare::isEqual(mx5[1][0], mrc[2]));
            Assert::IsTrue(FloatCompare::isEqual(mx5(1, 0), mrc[2]));
            Vector2 v1 = Vector2(mrc[0], mrc[1]);
            Vector2 v2 = Vector2(mrc[2], mrc[3]);
            Matrix2 mx7;
            mx7.setRow(0, v1); mx7.setRow(1, v2);
            Assert::IsTrue(mx5 == mx7);
            Vector2 v3 = Vector2(mrc[0], mrc[2]);
            Vector2 v4 = Vector2(mrc[1], mrc[3]);
            Matrix2 mx8;
            mx8.setColumn(0, v3); mx8.setColumn(1, v4);
            Assert::IsTrue(mx5 == mx8);
            float* mrc1 = (float*)mx8;
            Assert::IsTrue(FloatCompare::isEqual(mrc1[0], mrc[0]));
            Assert::IsTrue(FloatCompare::isEqual(mrc1[3], mrc[3]));
            Vector2 v5 = mx8.getRow(0);
            Assert::IsTrue(v5 == v1);
            Vector2 v6 = mx7.getColumn(1);
            Assert::IsTrue(v6 == v4);
            //float mrc2[4];
            //mx7.getColumnMajor(mrc2);
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[0], mrc[0]));
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[1], mrc[2]));
            mx7 = mx1;
            Assert::IsTrue(mx7 == mx1);
            Assert::IsTrue(mx5 + mx6 == 2.0f * mx5);
            Assert::IsTrue(3.0f * mx8 == mx8 * 3.0f);
            Assert::IsTrue(mx5 - mx6 == Matrix2::ZERO);
            Assert::IsTrue(Matrix2::ZERO - mx5 == -mx6);
            Assert::IsTrue(mx5 / 2.0f == 0.5f * mx6);
            mx7 = mx5;
            mx7 += mx6;
            Assert::IsTrue(mx7 == 2.0f * mx5);
            mx7 -= mx5;
            Assert::IsTrue(mx7 == mx6);
            mx7 *= 2.0f;
            Assert::IsTrue(mx7 == 2.0f * mx6);
            mx7 /= 4.0f;
            Assert::IsTrue(mx7 == mx6 / 2.0f);
            mx8 = mx5.inverse();
            Assert::IsTrue(mx8 * mx5 == Matrix2::IDENTITY);
            mx7 = mx5.transpose();
            mx7 = mx7.transpose();
            Assert::IsTrue(mx7 == mx5);
        }

        TEST_METHOD(Matrix3Test)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> pi_rand(-Constants::PI, Constants::PI);
            std::uniform_real_distribution<float> half_pi_rand(-Constants::HALF_PI, Constants::HALF_PI);
            Matrix3 mx1 = Matrix3::IDENTITY;
            Assert::IsTrue(mx1 == Matrix3::IDENTITY);
            Matrix3 mx2 = Matrix3();
            Assert::IsTrue(mx2 == Matrix3::ZERO);
            Radian angle = Radian(pi_rand(generator));
            if (angle.value() < 0.0f) angle = -angle;
            Vector3 axis0 = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis0.normalizeSelf();
            //Matrix3 mxa(axis0, angle);
            mx1 = Matrix3::fromAxisAngle(axis0, angle);
            //Assert::IsTrue(mx1 == mxa);
            Radian angle2;
            Vector3 axis1;
            std::tie(axis1, angle2) = mx1.toAxisAngle();
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(angle == angle2);
            Assert::IsTrue(axis1 == axis0);
            Matrix3 mx3 = Matrix3(unif_rand(generator), unif_rand(generator), unif_rand(generator),
                unif_rand(generator), unif_rand(generator), unif_rand(generator),
                unif_rand(generator), unif_rand(generator), unif_rand(generator));
            mx3 = Matrix3::makeIdentity();
            Assert::IsTrue(mx3 == Matrix3::IDENTITY);
            mx3 = Matrix3::makeZero();
            Assert::IsTrue(mx3 == Matrix3::ZERO);
            float m00 = unif_rand(generator);
            float m11 = unif_rand(generator);
            float m22 = unif_rand(generator);
            mx3 = Matrix3::makeDiagonal(m00, m11, m22);
            Matrix3 mx4 = Matrix3(m00, 0.0f, 0.0f, 0.0f, m11, 0.0f, 0.0f, 0.0f, m22);
            Assert::IsTrue(mx3 == mx4);
            std::array<float, 9> mrc;
            mrc[0] = unif_rand(generator); mrc[1] = unif_rand(generator);   mrc[2] = unif_rand(generator);
            mrc[3] = unif_rand(generator); mrc[4] = unif_rand(generator); mrc[5] = unif_rand(generator);
            mrc[6] = unif_rand(generator); mrc[7] = unif_rand(generator); mrc[8] = unif_rand(generator);
            Matrix3 mx5 = Matrix3(mrc[0], mrc[1], mrc[2], mrc[3], mrc[4], mrc[5], mrc[6], mrc[7], mrc[8]);
            Matrix3 mx6 = Matrix3(mrc);
            Assert::IsTrue(mx5 == mx6);
            Assert::IsTrue(FloatCompare::isEqual(mx5[0][0], mrc[0]));
            Assert::IsTrue(FloatCompare::isEqual(mx5[1][0], mrc[3]));
            Assert::IsTrue(FloatCompare::isEqual(mx5[1][1], mrc[4]));
            Assert::IsTrue(FloatCompare::isEqual(mx5(2, 0), mrc[6]));
            Vector3 v1 = Vector3(mrc[0], mrc[1], mrc[2]);
            Vector3 v2 = Vector3(mrc[3], mrc[4], mrc[5]);
            Vector3 v3 = Vector3(mrc[6], mrc[7], mrc[8]);

            Matrix3 mx7;
            mx7.setRow(0, v1); mx7.setRow(1, v2); mx7.setRow(2, v3);
            Assert::IsTrue(mx5 == mx7);
            Matrix3 mx10 = Matrix3::fromRowVectors({ v1, v2, v3 });
            Assert::IsTrue(mx10 == mx7);
            Vector3 v4 = Vector3(mrc[0], mrc[3], mrc[6]);
            Vector3 v5 = Vector3(mrc[1], mrc[4], mrc[7]);
            Vector3 v6 = Vector3(mrc[2], mrc[5], mrc[8]);
            Matrix3 mx8;
            mx8.setColumn(0, v4); mx8.setColumn(1, v5); mx8.setColumn(2, v6);
            Assert::IsTrue(mx5 == mx8);
            Matrix3 mx11 = Matrix3::fromColumnVectors({ v4, v5, v6 });
            Assert::IsTrue(mx8 == mx11);
            //Vector3 av[6] = { v1,v2,v3,v4,v5,v6 };
            //Matrix3 mx12 = Matrix3(&av[0], false);
            //Assert::IsTrue(mx12 == mx10);
            //Matrix3 mx13 = Matrix3(&av[3], true);
            //Assert::IsTrue(mx13 == mx11);
            float* mrc1 = (float*)mx8;
            Assert::IsTrue(FloatCompare::isEqual(mrc1[0], mrc[0]));
            Assert::IsTrue(FloatCompare::isEqual(mrc1[7], mrc[7]));
            Vector3 v7 = mx8.getRow(0);
            Assert::IsTrue(v7 == v1);
            Vector3 v8 = mx7.getColumn(1);
            Assert::IsTrue(v8 == v5);
            //float mrc2[9];
            //mx7.GetColumnMajor(mrc2);
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[0], mrc[0]));
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[7], mrc[5]));
            //Matrix3 mx9 = Matrix3(mrc2);
            //mx9 = mx9.Transpose();
            //Assert::IsTrue(mx9 == mx7);
            mx7 = mx1;
            Assert::IsTrue(mx7 == mx1);
            Assert::IsTrue(mx5 + mx6 == 2.0f * mx5);
            Assert::IsTrue(3.0f * mx8 == mx8 * 3.0f);
            Assert::IsTrue(mx5 - mx6 == Matrix3::ZERO);
            Assert::IsTrue(Matrix3::ZERO - mx5 == -mx6);
            Assert::IsTrue(mx5 / 2.0f == 0.5f * mx6);
            mx7 = mx5;
            mx7 += mx6;
            Assert::IsTrue(mx7 == 2.0f * mx5);
            mx7 -= mx5;
            Assert::IsTrue(mx7 == mx6);
            mx7 *= 2.0f;
            Assert::IsTrue(mx7 == 2.0f * mx6);
            mx7 /= 4.0f;
            Assert::IsTrue(mx7 == mx6 / 2.0f);
            mx8 = mx5.inverse();
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(mx8 * mx5 == Matrix3::IDENTITY);
            mx7 = mx5.transpose();
            mx7 = mx7.transpose();
            //Math::m_epsilonUlp = 1.0f;
            Assert::IsTrue(mx7 == mx5);

            Radian yaw = Radian(pi_rand(generator));
            Radian pitch = Radian(half_pi_rand(generator));
            Radian roll = Radian(pi_rand(generator));
            Matrix3 mx20;
            mx20 = fromEulerAnglesXyz(EulerAngles{ yaw, pitch, roll });
            EulerAngles euler1;
            euler1 = toEulerAnglesXyz(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);
            yaw = Radian(pi_rand(generator));
            pitch = Radian(pi_rand(generator));
            roll = Radian(half_pi_rand(generator));
            mx20 = fromEulerAnglesXzy(EulerAngles{ yaw, pitch, roll });
            euler1 = toEulerAnglesXzy(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);
            yaw = Radian(half_pi_rand(generator));
            pitch = Radian(pi_rand(generator));
            roll = Radian(pi_rand(generator));
            mx20 = fromEulerAnglesYxz(EulerAngles{ yaw, pitch, roll });
            euler1 = toEulerAnglesYxz(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);
            yaw = Radian(pi_rand(generator));
            pitch = Radian(pi_rand(generator));
            roll = Radian(half_pi_rand(generator));
            yaw = Radian(pi_rand(generator));
            pitch = Radian(pi_rand(generator));
            roll = Radian(half_pi_rand(generator));
            mx20 = fromEulerAnglesYzx(EulerAngles{ yaw, pitch, roll });
            euler1 = toEulerAnglesYzx(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);
            yaw = Radian(half_pi_rand(generator));
            pitch = Radian(pi_rand(generator));
            roll = Radian(pi_rand(generator));
            mx20 = fromEulerAnglesZxy(EulerAngles{ yaw, pitch, roll });
            euler1 = toEulerAnglesZxy(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);
            yaw = Radian(pi_rand(generator));
            pitch = Radian(half_pi_rand(generator));
            roll = Radian(pi_rand(generator));
            mx20 = fromEulerAnglesZyx(EulerAngles{ yaw, pitch, roll });
            euler1 = toEulerAnglesZyx(mx20);
            Assert::IsTrue(yaw == euler1.m_x);
            Assert::IsTrue(pitch == euler1.m_y);
            Assert::IsTrue(roll == euler1.m_z);

            Matrix3 mxp;
            mxp = Matrix3::rotationX(pitch);
            Matrix3 mx21;
            mx21 = Matrix3::fromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), pitch);
            Assert::IsTrue(mxp == mx21);
            Matrix3 mxy;
            mxy = Matrix3::rotationY(yaw);
            mx21 = Matrix3::fromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), yaw);
            Assert::IsTrue(mxy == mx21);
            Matrix3 mxr;
            mxr = Matrix3::rotationZ(roll);
            mx21 = Matrix3::fromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), roll);
            Assert::IsTrue(mx21 == mxr);
            Matrix3 mxrpy;
            mxrpy = Matrix3::rotationYawPitchRoll(yaw, pitch, roll);
            mx21 = fromEulerAnglesYxz(EulerAngles{ pitch, yaw, roll });
            Assert::IsTrue(mx21 == mxrpy);
            mx21 = mxy * mxp * mxr;
            Assert::IsTrue(mx21 == mxrpy);
        }
        TEST_METHOD(Matrix4Test)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            Matrix4 mx1 = Matrix4::IDENTITY;
            Assert::IsTrue(mx1 == Matrix4::IDENTITY);
            Matrix4 mx2 = Matrix4();
            Assert::IsTrue(mx2 == Matrix4::ZERO);
            Matrix4 mx3 = Matrix4(unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator),
                unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator),
                unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator),
                unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator));
            mx3 = Matrix4::makeIdentity();
            Assert::IsTrue(mx3 == Matrix4::IDENTITY);
            mx3 = Matrix4::makeZero();
            Assert::IsTrue(mx3 == Matrix4::ZERO);
            std::array<float, 16> mrc;
            mrc[0] = unif_rand(generator); mrc[1] = unif_rand(generator);   mrc[2] = unif_rand(generator);  mrc[3] = unif_rand(generator);
            mrc[4] = unif_rand(generator); mrc[5] = unif_rand(generator);       mrc[6] = unif_rand(generator); mrc[7] = unif_rand(generator);
            mrc[8] = unif_rand(generator); mrc[9] = unif_rand(generator); mrc[10] = unif_rand(generator); mrc[11] = unif_rand(generator);
            mrc[12] = unif_rand(generator); mrc[13] = unif_rand(generator); mrc[14] = unif_rand(generator); mrc[15] = unif_rand(generator);

            Matrix4 mx5 = Matrix4(mrc[0], mrc[1], mrc[2], mrc[3], mrc[4], mrc[5], mrc[6], mrc[7], mrc[8],
                mrc[9], mrc[10], mrc[11], mrc[12], mrc[13], mrc[14], mrc[15]);
            Matrix4 mx6 = Matrix4(mrc);
            Assert::IsTrue(mx5 == mx6);
            Assert::IsTrue(FloatCompare::isEqual(mx5[0][0], mrc[0]));
            Assert::IsTrue(FloatCompare::isEqual(mx5[1][0], mrc[4]));
            Assert::IsTrue(FloatCompare::isEqual(mx5[1][1], mrc[5]));
            Assert::IsTrue(FloatCompare::isEqual(mx5(2, 0), mrc[8]));
            Assert::IsTrue(FloatCompare::isEqual(mx5(3, 2), mrc[14]));
            Vector4 v1 = Vector4(mrc[0], mrc[1], mrc[2], mrc[3]);
            Vector4 v2 = Vector4(mrc[4], mrc[5], mrc[6], mrc[7]);
            Vector4 v3 = Vector4(mrc[8], mrc[9], mrc[10], mrc[11]);
            Vector4 va = Vector4(mrc[12], mrc[13], mrc[14], mrc[15]);

            Matrix4 mx7;
            mx7.setRow(0, v1); mx7.setRow(1, v2); mx7.setRow(2, v3); mx7.setRow(3, va);
            Assert::IsTrue(mx5 == mx7);
            Vector4 v4 = Vector4(mrc[0], mrc[4], mrc[8], mrc[12]);
            Vector4 v5 = Vector4(mrc[1], mrc[5], mrc[9], mrc[13]);
            Vector4 v6 = Vector4(mrc[2], mrc[6], mrc[10], mrc[14]);
            Vector4 vb = Vector4(mrc[3], mrc[7], mrc[11], mrc[15]);
            Matrix4 mx8;
            mx8.setColumn(0, v4); mx8.setColumn(1, v5); mx8.setColumn(2, v6); mx8.setColumn(3, vb);
            Assert::IsTrue(mx5 == mx8);

            float* mrc1 = (float*)mx8;
            Assert::IsTrue(FloatCompare::isEqual(mrc1[0], mrc[0]));
            Assert::IsTrue(FloatCompare::isEqual(mrc1[7], mrc[7]));
            Vector4 v7 = mx8.getRow(0);
            Assert::IsTrue(v7 == v1);
            Vector4 v8 = mx7.getColumn(1);
            Assert::IsTrue(v8 == v5);
            //float mrc2[16];
            //mx7.GetColumnMajor(mrc2);
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[0], mrc[0]));
            //Assert::IsTrue(FloatCompare::isEqual(mrc2[7], mrc[13]));
            //Matrix4 mx9 = Matrix4(mrc2);
            //mx9 = mx9.Transpose();
            //Assert::IsTrue(mx9 == mx7);

            mx7 = mx1;
            Assert::IsTrue(mx7 == mx1);
            Assert::IsTrue(mx5 + mx6 == 2.0f * mx5);
            Assert::IsTrue(3.0f * mx8 == mx8 * 3.0f);
            Assert::IsTrue(mx5 - mx6 == Matrix4::ZERO);
            Assert::IsTrue(Matrix4::ZERO - mx5 == -mx6);
            Assert::IsTrue(mx5 / 2.0f == 0.5f * mx6);
            mx7 = mx5;
            mx7 += mx6;
            Assert::IsTrue(mx7 == 2.0f * mx5);
            mx7 -= mx5;
            Assert::IsTrue(mx7 == mx6);
            mx7 *= 2.0f;
            Assert::IsTrue(mx7 == 2.0f * mx6);
            mx7 /= 4.0f;
            Assert::IsTrue(mx7 == mx6 / 2.0f);
            mx8 = mx5.inverse();
            FloatCompare::epsilonUlp(10.0f);
            Assert::IsTrue(mx8 * mx5 == Matrix4::IDENTITY);
            mx7 = mx5.transpose();
            mx7 = mx7.transpose();
            //Math::m_epsilonUlp = 1.0f;
            Assert::IsTrue(mx7 == mx5);

            Vector3 v31 = Vector3(mrc[0], mrc[1], mrc[2]);
            Vector3 v32 = Vector3(mrc[4], mrc[5], mrc[6]);
            Vector3 v33 = Vector3(mrc[8], mrc[9], mrc[10]);
            Point3 p34 = Point3(0.0f, 0.0f, 0.0f);
            //Vector3 av3[4] = { v31,v32,v33,v34 };

            Matrix4 mx10_4 = Matrix4(Matrix3::fromRowVectors({ v31, v32, v33 }), p34);
            Matrix3 mx10_3 = Matrix3::fromRowVectors({ v31, v32, v33 });
            Matrix4 mx11_4(mx10_3);
            Assert::IsTrue(mx11_4 == mx10_4);
            Matrix3 mx11_3(mx10_4);
            Assert::IsTrue(mx11_3 == mx10_3);
            //Matrix4 mx12_4 = Matrix4(av3, false);
            //Assert::IsTrue(mx12_4 == mx10_4);

            mx10_4 = Matrix4(Matrix3::fromColumnVectors({ v31, v32, v33 }), p34);
            mx10_3 = Matrix3::fromColumnVectors({ v31, v32, v33 });
            mx11_4 = mx10_3;
            Assert::IsTrue(mx11_4 == mx10_4);
            mx11_3 = mx10_4;
            Assert::IsTrue(mx11_3 == mx10_3);
            //mx12_4 = Matrix4(av3, true);
            //Assert::IsTrue(mx12_4 == mx10_4);

            Vector4 v10 = Vector4(unif_rand(generator), unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector4 v11 = mx5 * v10;
            Vector4 v12;
            for (int i = 0; i < 4; i++)
            {
                v12.x(v12.x() + mx5[0][i] * v10[i]);
                v12.y(v12.y() + mx5[1][i] * v10[i]);
                v12.z(v12.z() + mx5[2][i] * v10[i]);
                v12.w(v12.w() + mx5[3][i] * v10[i]);
            }
            Assert::IsTrue(v11 == v12);

            Point3 p301 = Point3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Point3 p302 = mx5 * p301;
            Vector4 v401 = Vector4(p301.x(), p301.y(), p301.z(), 1.0f);
            Vector4 v402 = mx5 * v401;
            Vector3 v303 = Vector3(v402.x() / v402.w(), v402.y() / v402.w(), v402.z() / v402.w());
            Vector3 v302 = Vector3(p302.x(), p302.y(), p302.z());
            Assert::IsTrue(v302 == v303);

            Point3 p304 = mx5 * p301;
            Assert::IsTrue(p304 == p302);
            Vector3 v301 = Vector3(p301.x(), p301.y(), p301.z());
            Vector4 v403 = Vector4(v301.x(), v301.y(), v301.z(), 0.0f);
            Vector4 v404 = mx5 * v403;
            Vector3 v306 = mx5 * v301;
            Assert::IsTrue(FloatCompare::isEqual(v306.x(), v404.x()));
            Assert::IsTrue(FloatCompare::isEqual(v306.y(), v404.y()));
            Assert::IsTrue(FloatCompare::isEqual(v306.z(), v404.z()));

            std::uniform_real_distribution<float> pi_rand(-Constants::PI, Constants::PI);
            std::uniform_real_distribution<float> half_pi_rand(-Constants::HALF_PI, Constants::HALF_PI);
            Radian yaw = Radian(half_pi_rand(generator));
            Radian pitch = Radian(half_pi_rand(generator));
            Radian roll = Radian(half_pi_rand(generator));

            Matrix3 mx20;
            mx20 = Matrix3::rotationYawPitchRoll(yaw, pitch, roll);
            Matrix4 mx21;
            mx21 = Matrix4::makeRotationYawPitchRoll(yaw, pitch, roll);
            Matrix4 mx420(mx20);
            Assert::IsTrue(mx420 == mx21);

            Matrix3 mx3p;
            mx3p = Matrix3::rotationX(pitch);
            Matrix4 mx4p;
            mx4p = Matrix4::makeRotationXTransform(pitch);
            Matrix4 mx34p(mx3p);
            Assert::IsTrue(mx34p == mx4p);

            Matrix3 mx3y;
            mx3y = Matrix3::rotationY(yaw);
            Matrix4 mx4y;
            mx4y = Matrix4::makeRotationYTransform(yaw);
            Matrix4 mx34y(mx3y);
            Assert::IsTrue(mx34y == mx4y);

            Matrix3 mx3r;
            mx3r = Matrix3::rotationZ(roll);
            Matrix4 mx4r;
            mx4r = Matrix4::makeRotationZTransform(roll);
            Matrix4 mx34r(mx3r);
            Assert::IsTrue(mx34r == mx4r);

            Matrix3 mx3rpy;
            mx3rpy = Matrix3::rotationYawPitchRoll(yaw, pitch, roll);
            Matrix4 mx34rpy(mx3rpy);
            Matrix4 mx4rpy;
            mx4rpy = Matrix4::makeRotationYawPitchRoll(yaw, pitch, roll);
            Assert::IsTrue(mx34rpy == mx4rpy);
            mx4rpy = mx4y * mx4p * mx4r;
            Assert::IsTrue(mx34rpy == mx4rpy);

            Point3 vpos = Point3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector3 vscale = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Matrix4 mxpos;
            mxpos = Matrix4::makeTranslateTransform(vpos);
            Matrix4 mxscale;
            mxscale = Matrix4::makeScaleTransform(vscale);
            Matrix4 mxsum = mxpos * mx4rpy * mxscale;

            Point3 vpos1 = mxsum.extractTranslation();
            Vector3 vscale1 = mxsum.extractScale();
            Matrix4 mx4rpy1(mxsum.extractRotation());
            Matrix4 mxpos1;
            mxpos1 = Matrix4::makeTranslateTransform(vpos1);
            Matrix4 mxscale1;
            mxscale1 = Matrix4::makeScaleTransform(vscale1);
            Matrix4 mxsum1 = mxpos1 * mx4rpy1 * mxscale1;
            Assert::IsTrue(mxsum == mxsum1);
        }
    };
}
