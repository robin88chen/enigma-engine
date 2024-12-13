#include "Triangle2.hpp"
#include "Vector2.hpp"
#include <cmath>

using namespace Math;

Triangle2::Triangle2() : m_points{ Point2::ZERO, Point2::ZERO, Point2::ZERO }
{
}

Triangle2::Triangle2(const Point2& p0, const Point2& p1, const Point2& p2) : m_points{ p0, p1, p2 }
{
}

Triangle2::Triangle2(const std::array<Point2, 3>& pts) : m_points(pts)
{
}

Point2 Triangle2::point(unsigned i) const
{
    return m_points[i];
}

void Triangle2::point(unsigned i, const Point2& p)
{
    m_points[i] = p;
}

bool Triangle2::operator==(const Triangle2& tri) const
{
    return m_points[0] == tri.m_points[0] && m_points[1] == tri.m_points[1] && m_points[2] == tri.m_points[2];
}

bool Triangle2::operator!=(const Triangle2& tri) const
{
    return m_points[0] != tri.m_points[0] || m_points[1] != tri.m_points[1] || m_points[2] != tri.m_points[2];
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
float Triangle2::distanceTo(const Point2& p) const
{
    const Vector2 diff = m_points[0] - p;
    const Vector2 edge0 = m_points[1] - m_points[0];
    const Vector2 edge1 = m_points[2] - m_points[0];
    const float a00 = edge0.squaredLength();
    const float a01 = edge0.dot(edge1);
    const float a11 = edge1.squaredLength();
    const float b0 = diff.dot(edge0);
    const float b1 = diff.dot(edge1);
    const float c = diff.squaredLength();
    const float det = std::abs(a00 * a11 - a01 * a01);
    float s = a01 * b1 - a11 * b0;
    float t = a01 * b0 - a00 * b1;
    float sqr_dist; // NOLINT(cppcoreguidelines-init-variables)

    if (s + t <= det)
    {
        if (s < 0.0f)
        {
            if (t < 0.0f) // region 4
            {
                if (b0 < 0.0f)
                {
                    if (-b0 >= a00)
                    {
                        sqr_dist = a00 + 2.0f * b0 + c;
                    }
                    else
                    {
                        sqr_dist = c - b0 * b0 / a00;
                    }
                }
                else
                {
                    if (b1 >= 0.0f)
                    {
                        sqr_dist = c;
                    }
                    else if (-b1 >= a11)
                    {
                        sqr_dist = a11 + 2.0f * b1 + c;
                    }
                    else
                    {
                        sqr_dist = c - b1 * b1 / a11;
                    }
                }
            }
            else // region 3
            {
                if (b1 >= 0.0f)
                {
                    sqr_dist = c;
                }
                else if (-b1 >= a11)
                {
                    sqr_dist = a11 + 2.0f * b1 + c;
                }
                else
                {
                    sqr_dist = c - b1 * b1 / a11;
                }
            }
        }
        else if (t < 0.0f) // region 5
        {
            if (b0 >= 0.0f)
            {
                sqr_dist = c;
            }
            else if (-b0 >= a00)
            {
                sqr_dist = a00 + 2.0f * b0 + c;
            }
            else
            {
                sqr_dist = b0 * s + c - b0 * b0 / a00;
            }
        }
        else // region 0
        {
            // minimum at interior point
            const float inv_det = 1.0f / det;
            s *= inv_det;
            t *= inv_det;
            sqr_dist = s * (a00 * s + a01 * t + 2.0f * b0) +
                t * (a01 * s + a11 * t + 2.0f * b1) + c;
        }
    }
    else
    {
        if (s < 0.0f) // region 2
        {
            const float tmp0 = a01 + b0;
            if (const float tmp1 = a11 + b1; tmp1 > tmp0)
            {
                const float numer = tmp1 - tmp0;
                const float denom = a00 - 2.0f * a01 + a11;
                if (numer >= denom)
                {
                    sqr_dist = a00 + 2.0f * b0 + c;
                }
                else
                {
                    s = numer / denom;
                    t = 1.0f - s;
                    sqr_dist = s * (a00 * s + a01 * t + 2.0f * b0) +
                        t * (a01 * s + a11 * t + 2.0f * b1) + c;
                }
            }
            else
            {
                if (tmp1 <= 0.0f)
                {
                    sqr_dist = a11 + 2.0f * b1 + c;
                }
                else if (b1 >= 0.0f)
                {
                    sqr_dist = c;
                }
                else
                {
                    sqr_dist = c - b1 * b1 / a11;
                }
            }
        }
        else if (t < 0.0f) // region 6
        {
            const float tmp0 = a01 + b1;
            if (const float tmp1 = a00 + b0; tmp1 > tmp0)
            {
                const float numer = tmp1 - tmp0;
                if (const float denom = a00 - 2.0f * a01 + a11; numer >= denom)
                {
                    sqr_dist = a11 + 2.0f * b1 + c;
                }
                else
                {
                    t = numer / denom;
                    s = 1.0f - t;
                    sqr_dist = s * (a00 * s + a01 * t + 2.0f * b0) +
                        t * (a01 * s + a11 * t + 2.0f * b1) + c;
                }
            }
            else
            {
                if (tmp1 <= 0.0f)
                {
                    sqr_dist = a00 + 2.0f * b0 + c;
                }
                else if (b0 >= 0.0f)
                {
                    sqr_dist = c;
                }
                else
                {
                    sqr_dist = c - b0 * b0 / a00;
                }
            }
        }
        else // region 1
        {
            if (const float numer = a11 + b1 - a01 - b0; numer <= 0.0f)
            {
                sqr_dist = a11 + 2.0f * b1 + c;
            }
            else
            {
                const float denom = a00 - 2.0f * a01 + a11;
                if (numer >= denom)
                {
                    sqr_dist = a00 + 2.0f * b0 + c;
                }
                else
                {
                    s = numer / denom;
                    t = 1.0f - s;
                    sqr_dist = s * (a00 * s + a01 * t + 2.0f * b0) +
                        t * (a01 * s + a11 * t + 2.0f * b1) + c;
                }
            }
        }
    }

    return std::sqrt(std::abs(sqr_dist));
}
// NOLINTEND(readability-function-cognitive-complexity)
