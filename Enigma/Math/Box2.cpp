#include "Box2.hpp"
#include "MathGlobal.hpp"
#include <cmath>
#include <cassert>

using namespace Math;

Box2::Box2() : m_center(Point2::ZERO), m_axis{ Vector2::UNIT_X, Vector2::UNIT_Y }, m_extent{ 0.0f, 0.0f }
{
}

Box2::Box2(const Point2& center, const std::array<Vector2, 2>& axis, const std::array<float, 2>& extents)
    : m_center(center), m_axis(axis), m_extent(extents)
{
    assert(isValid());
}

Box2::Box2(const Point2& center, const Vector2& axis0, const Vector2& axis1, float extent0, float extent1)
    : m_center(center), m_axis{ axis0, axis1 }, m_extent{ extent0, extent1 }
{
    assert(isValid());
}

bool Box2::isValid() const
{
    return m_axis[0].isUnitLength() && m_axis[1].isUnitLength() && m_extent[0] >= 0.0f && m_extent[1] >= 0.0f && std::abs(m_axis[0].dot(m_axis[1])) <= FloatCompare::zeroTolerance();
}

Point2 Box2::center() const
{
    return m_center;
}

void Box2::center(const Point2& center)
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
    assert(axis[0].isUnitLength() && axis[1].isUnitLength() && std::abs(axis[0].dot(axis[1])) <= FloatCompare::zeroTolerance());
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

std::array<Point2, Box2::VERTICES_COUNT> Box2::computeVertices() const
{
    std::array<Point2, VERTICES_COUNT> vertices;
    const Vector2 product0 = m_extent[0] * m_axis[0];
    const Vector2 product1 = m_extent[1] * m_axis[1];
    vertices[0] = m_center + (-product0 - product1);
    vertices[1] = m_center + (product0 - product1);
    vertices[2] = m_center + (product0 + product1);
    vertices[3] = m_center + (-product0 + product1);
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

bool Box2::contains(const Point2& p) const
{
    const Vector2 diff = p - m_center;
    if (const float diff_dot0 = std::abs(diff.dot(m_axis[0])); diff_dot0 > m_extent[0] + FloatCompare::tolerance(diff_dot0, m_extent[0])) return false;
    if (const float diff_dot1 = std::abs(diff.dot(m_axis[1])); diff_dot1 > m_extent[1] + FloatCompare::tolerance(diff_dot1, m_extent[1])) return false;
    return true;
}
