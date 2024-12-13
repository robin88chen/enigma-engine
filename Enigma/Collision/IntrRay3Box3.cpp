#include "IntrRay3Box3.hpp"
#include "Math/MathGlobal.hpp"
#include <cassert>
#include <cmath>

using namespace Collision;

IntrRay3Box3::IntrRay3Box3(const Math::Ray3& ray, const Math::Box3& box) : m_ray(ray), m_box(box), m_quantity(0), m_tParam{}
{
}

const Math::Ray3& IntrRay3Box3::ray() const
{
    return m_ray;
}

const Math::Box3& IntrRay3Box3::box() const
{
    return m_box;
}

bool IntrRay3Box3::test()
{
    /** RayOBB intersection, form Real-time Rendering p574 */
    float tmin = -Math::Constants::MAX_FLOAT;
    float tmax = Math::Constants::MAX_FLOAT;
    const Math::Vector3 p = m_box.center() - m_ray.origin();

    for (unsigned i = 0; i < 3; i++)
    {
        const float e = m_box.axis(i).dot(p);
        const float f = m_box.axis(i).dot(m_ray.direction());
        if (std::abs(f) > Math::FloatCompare::zeroTolerance()) // 軸跟方向不是垂直的, 射線跟slab plane有交點
        {
            float t1 = (e + m_box.extent(i)) / f;
            float t2 = (e - m_box.extent(i)) / f;
            // make sure t1<t2
            if (t1 > t2)
            {
                std::swap(t1, t2);
            }
            if (t1 > tmin) tmin = t1;
            if (t2 < tmax) tmax = t2;

            if (tmin > tmax) return false;
            if (tmax < 0.0f) return false;
        }
        else if ((-e - m_box.extent(i) > 0.0f) || (-e + m_box.extent(i) < 0.0f)) return false; // 射線與slab plane是平行的，所以要確認射線的原點是否在兩slab plane中間
    }

    if (tmin > 0.0f)
    {
        m_point[m_quantity] = tmin * m_ray.direction() + m_ray.origin();
        m_tParam[m_quantity] = tmin;
        m_quantity++;
    }
    if (tmax > 0.0f)
    {
        m_point[m_quantity] = tmax * m_ray.direction() + m_ray.origin();
        m_tParam[m_quantity] = tmax;
        m_quantity++;
    }
    if (m_quantity == 0) return false;
    return true;
}

bool IntrRay3Box3::find()
{
    // 因為沒有多少運算上的差異，所以直接呼叫Test
    return test();
}

unsigned IntrRay3Box3::getQuantity() const
{
    return m_quantity;
}

const Math::Point3& IntrRay3Box3::getPoint(unsigned i) const
{
    assert(i < m_quantity);
    return m_point[i];
}

float IntrRay3Box3::getRayT(unsigned i) const
{
    assert(i < m_quantity);
    return m_tParam[i];
}
