#include "Box2.hpp"
#include "MathGlobal.hpp"
#include <cmath>
#include <cassert>

using namespace Math;

Box2::Box2() : m_center(Vector2::ZERO), m_axis{ Vector2::UNIT_X, Vector2::UNIT_Y }, m_extent{ 0.0f, 0.0f }
{
}

Box2::Box2(const Vector2& center, const std::array<Vector2, 2>& axis, const std::array<float, 2>& extents)
    : m_center(center), m_axis(axis), m_extent(extents)
{
    assert(isValid());
}

Box2::Box2(const Vector2& center, const Vector2& axis0, const Vector2& axis1, float extent0, float extent1)
    : m_center(center), m_axis{ axis0, axis1 }, m_extent{ extent0, extent1 }
{
    assert(isValid());
}

bool Box2::isValid() const
{
    return m_axis[0].isUnitLength() && m_axis[1].isUnitLength() && m_extent[0] >= 0.0f && m_extent[1] >= 0.0f && std::abs(m_axis[0].dotPerpendicular(m_axis[1])) <= FloatCompare::ZERO_TOLERANCE;
}

Vector2 Box2::center() const
{
    return m_center;
}

void Box2::center(const Vector2& center)
{
    m_center = center;
}

Vector2 Box2::axis(unsigned index) const
{
    assert(index <= 1);
    return m_axis[index];
}

const std::array<Vector2, 2>& Box2::axis() const
{
    return m_axis;
}

void Box2::axis(const std::array<Vector2, 2>& axis)
{
    assert(axis[0].isUnitLength() && axis[1].isUnitLength() && std::abs(axis[0].dotPerpendicular(axis[1])) <= FloatCompare::ZERO_TOLERANCE);
    m_axis = axis;
}

float Box2::extent(unsigned index) const
{
    assert(index <= 1);
    return m_extent[index];
}

const std::array<float, 2>& Box2::extent() const
{
    return m_extent;
}

void Box2::extent(unsigned index, float extent)
{
    assert(index <= 1);
    assert(extent >= 0.0f);
    m_extent[index] = extent;
}

std::array<Vector2, Box2::VERTICES_COUNT> Box2::computeVertices() const
{
    std::array<Vector2, VERTICES_COUNT> vertices;
    const Vector2 product0 = m_extent[0] * m_axis[0];
    const Vector2 product1 = m_extent[1] * m_axis[1];
    vertices[0] = m_center - product0 - product1;
    vertices[1] = m_center + product0 - product1;
    vertices[2] = m_center + product0 + product1;
    vertices[3] = m_center - product0 + product1;
    return vertices;
}

bool Box2::operator== (const Box2& box) const
{
    return m_center == box.m_center && m_axis == box.m_axis && FloatCompare::isEqual(m_extent[0], box.m_extent[0]) && FloatCompare::isEqual(m_extent[1], box.m_extent[1]);
}

bool Box2::operator!= (const Box2& box) const
{
    return m_center != box.m_center || m_axis != box.m_axis || !FloatCompare::isEqual(m_extent[0], box.m_extent[0]) || !FloatCompare::isEqual(m_extent[1], box.m_extent[1]);
}
