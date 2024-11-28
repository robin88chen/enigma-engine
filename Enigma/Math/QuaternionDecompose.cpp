#include "QuaternionDecompose.hpp"
#include "Vector3.hpp"
#include "MathGlobal.hpp"
#include <cmath>

namespace Math
{
    Quaternion align(const Vector3& vec1, const Vector3& vec2)
    {
        // If V1 and V2 are not parallel, the axis of rotation is the unit-length
        // vector U = cross(V1,V2)/length(cross(V1,V2)).  The angle of rotation,
        // A, is the angle between V1 and V2.  The quaternion for the rotation is
        // q = cos(A/2) + sin(A/2)*(ux*i+uy*j+uz*k) where U = (ux,uy,uz).
        //
        // (1) Rather than extract A = acos(dot(V1,V2)), multiply by 1/2, then
        //     compute sin(A/2) and cos(A/2), we reduce the computational costs by
        //     computing the bisector B = (V1+V2)/length(V1+V2), so cos(A/2) =
        //     dot(V1,B).
        //
        // (2) The rotation axis is U = cross(V1,B)/length(cross(V1,B)), but
        //     length(cross(V1,B)) = length(V1)*length(B)*sin(A/2) = sin(A/2), in
        //     which case sin(A/2)*(ux*i+uy*j+uz*k) = (cx*i+cy*j+cz*k) where
        //     C = cross(V1,B).
        //
        // If V1 and V2 are parallel, or nearly parallel as far as the Realing
        // point calculations are concerned, the calculation of B will produce
        // the zero vector: Vector3::Normalize checks for closeness to zero and
        // returns the zero vector accordingly.  Thus, we test for parallelism
        // by checking if cos(A/2) is zero.  The test for exactly zero is usually
        // not recommend for Realing point arithmetic, but the implementation of
        // Vector3::Normalize guarantees the comparison is robust.
        Vector3 bisector = vec1 + vec2;
        bisector.normalizeSelf();

        const float cos_half_angle = vec1.dot(bisector);

        const float w = cos_half_angle;
        float x; // NOLINT(cppcoreguidelines-init-variables)
        float y; // NOLINT(cppcoreguidelines-init-variables)
        float z; // NOLINT(cppcoreguidelines-init-variables)
        if (!FloatCompare::isEqual(cos_half_angle, 0.0f))
        {
            const Vector3 cross = vec1.cross(bisector);
            x = cross.x();
            y = cross.y();
            z = cross.z();
        }
        else
        {
            if (std::fabs(vec1[0]) >= std::fabs(vec1[1]))
            {
                // V1.x or V1.z is the largest magnitude component.
                const float inv_length = 1.0f / std::sqrt(vec1[0] * vec1[0] + vec1[2] * vec1[2]);
                x = -vec1[2] * inv_length;
                y = 0.0f;
                z = +vec1[0] * inv_length;
            }
            else
            {
                // V1.y or V1.z is the largest magnitude component.
                const float inv_length = 1.0f / std::sqrt(vec1[1] * vec1[1] + vec1[2] * vec1[2]);
                x = 0.0f;
                y = +vec1[2] * inv_length;
                z = -vec1[1] * inv_length;
            }
        }
        return { w, x, y, z };
    }

    QuaternionDecompose decomposeTwistTimesSwing(const Quaternion& q, const Vector3& vec1)
    {
        const Vector3 vec2 = q.rotate(vec1);
        const Quaternion swing = align(vec1, vec2);
        const Quaternion twist = q * swing.conjugate();
        return { swing, twist };
    }

    QuaternionDecompose decomposeSwingTimesTwist(const Quaternion& q, const Vector3& vec1)
    {
        const Vector3 vec2 = q.rotate(vec1);
        const Quaternion swing = align(vec1, vec2);
        const Quaternion twist = swing.conjugate() * q;
        return { swing, twist };
    }
}