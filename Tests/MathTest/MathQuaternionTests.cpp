#include "pch.h"
#include "CppUnitTest.h"
#include "Math/MathGlobal.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"
#include "Math/Radian.hpp"
#include "Math/Matrix3.hpp"
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Math;

namespace MathLibTests
{
    TEST_CLASS(MathQuaternionTests)
    {
    public:

        TEST_METHOD(QuaternionTest)
        {
            std::random_device rd;
            std::default_random_engine generator(rd());
            std::uniform_real_distribution<float> unif_rand(-10.0f, std::nextafter(10.0f, 10.1f));
            std::uniform_real_distribution<float> pi_rand(-Constants::PI, Constants::PI);
            std::uniform_real_distribution<float> half_pi_rand(-Constants::HALF_PI, Constants::HALF_PI);
            FloatCompare::epsilonUlp(10.0f);
            Quaternion q0 = Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
            Assert::IsTrue(q0 == Quaternion::ZERO);
            Quaternion q1 = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
            Assert::IsTrue(q1 == Quaternion::IDENTITY);
            Quaternion q2(q1);
            Assert::IsTrue(q2 == Quaternion::IDENTITY);
            float x = unif_rand(generator);
            float y = unif_rand(generator);
            float z = unif_rand(generator);
            float w = unif_rand(generator);
            Quaternion q3 = Quaternion(w, x, y, z);
            Assert::IsTrue(FloatCompare::isEqual(x, q3.x()));
            Assert::IsTrue(FloatCompare::isEqual(y, q3.y()));
            float* xyzw = (float*)q3;
            Assert::IsTrue(FloatCompare::isEqual(xyzw[0], q3.w()));

            Assert::IsTrue(FloatCompare::isEqual(q3.length(), sqrt(x * x + y * y + z * z + w * w)));
            Assert::IsTrue(FloatCompare::isEqual(q3.squaredLength(), (x * x + y * y + z * z + w * w)));
            Assert::IsTrue(FloatCompare::isEqual(q3.dot(q3), q3.squaredLength()));
            float q3len = q3.length();
            Quaternion nor_q = q3.normalize();
            Quaternion q3_l = q3 / q3.length();
            Assert::IsTrue(nor_q == q3_l);

            //   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)
            Vector3 axis = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            axis.normalizeSelf();
            Radian angle = Radian(pi_rand(generator));
            Quaternion q4 = Quaternion::fromAxisAngle(axis, angle);
            Assert::IsTrue(FloatCompare::isEqual(q4.x(), std::sin(0.5f * angle.value()) * axis.x()));
            Assert::IsTrue(FloatCompare::isEqual(q4.w(), std::cos(0.5f * angle.value())));
            Quaternion q5;
            q5 = Quaternion::fromAxisAngle(axis, angle);
            Assert::IsTrue(q4 == q5);
            Quaternion q6 = q5;
            Vector3 axis2;
            Radian angle2;
            std::tie(axis2, angle2) = q6.toAxisAngle();
            Assert::IsTrue(((axis == axis2) && (angle == angle2)) || ((axis == -axis2) && (angle == -angle2)));

            Radian yaw = Radian(half_pi_rand(generator));
            Radian pitch = Radian(half_pi_rand(generator));
            Radian roll = Radian(half_pi_rand(generator));

            Matrix3 mx_rot;
            mx_rot = Matrix3::rotationYawPitchRoll(yaw, pitch, roll);
            Quaternion q_rot;
            q_rot = Quaternion::fromRotationMatrix(mx_rot);
            Vector3 pos = Vector3(unif_rand(generator), unif_rand(generator), unif_rand(generator));
            Vector3 pos1 = mx_rot * pos;
            Vector3 pos2 = q_rot * pos;
            Assert::IsTrue(pos1 == pos2);
            Vector3 pos3 = q_rot.rotate(pos);
            Assert::IsTrue(pos3 == pos1);
            Matrix3 mx_rot2;
            mx_rot2 = q_rot.toRotationMatrix();
            Assert::IsTrue(mx_rot == mx_rot2);

            std::array<Vector3, 3> rot_column;
            rot_column[0] = mx_rot.getColumn(0); rot_column[1] = mx_rot.getColumn(1); rot_column[2] = mx_rot.getColumn(2);
            Quaternion q_rot2;
            q_rot2 = Quaternion::fromRotationMatrix(Matrix3::fromColumnVectors(rot_column));
            Assert::IsTrue(q_rot == q_rot2);
            Vector3 rot_column2[3];
            Matrix3 mx_rot3 = q_rot2.toRotationMatrix();
            Assert::IsTrue(rot_column[1] == mx_rot3.getColumn(1));

            Quaternion q7 = q5 + q6;
            Assert::IsTrue(q7 == 2.0f * q5);
            Quaternion q8 = q7 - q6;
            Assert::IsTrue(q8 == q5);
            Quaternion q9 = q7 / 2.0f;
            Assert::IsTrue(q9 == q8);
            Assert::IsTrue(q5 * 0.5 == q6 / 2.0f);

            Quaternion q10 = q5.inverse();
            Assert::IsTrue(q10 * q5 == Quaternion::IDENTITY);

            q7 += q6;
            Assert::IsTrue(q7 == 3.0f * q6);
            q7 -= q5;
            Assert::IsTrue(q7 == 2.0f * q6);
            q9 *= 2.0f;
            Assert::IsTrue(q9 == q7);
            q9 /= 2.0f;
            Assert::IsTrue(q9 == 0.5f * q7);

            Quaternion q11 = q5 + q5.conjugate();
            q11 = q11.normalize();
            Assert::IsTrue(q11 == Quaternion::IDENTITY);

            Quaternion q12(0.7f, 0.2f, 0.3f, 0.7f);
            Quaternion q13(1.0f, 0.0f, 0.0f, 0.0f);
            Quaternion q14 = Quaternion::sphericalLerp(0.8f, q12, q13);
            // 用網頁算,
            // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
            // 0.9873734753725321, 0.04436357818165539, 0.06654536727248309, 0.15527252363579386
            // 不過只有兩位 digit 是對的,
        }
    };
}
