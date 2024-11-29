﻿#include "Box3.hpp"
#include "MathGlobal.hpp"
#include <cassert>

using namespace Math;

Box3::Box3() : m_center(Vector3::ZERO), m_axis{ Vector3::UNIT_X, Vector3::UNIT_Y, Vector3::UNIT_Z }, m_extent{ 0.0f, 0.0f, 0.0f }
{
}

Box3::Box3(const Vector3& center, const std::array<Vector3, 3>& axis, const std::array<float, 3>& extent)
    : m_center(center), m_axis(axis), m_extent(extent)
{
    assert(isValid());
}

Box3::Box3(const Vector3& center, const Vector3& axis0, const Vector3& axis1, const Vector3& axis2,
    float extent0, float extent1, float extent2)
    : m_center(center), m_axis{ axis0, axis1, axis2 }, m_extent{ extent0, extent1, extent2 }
{
    assert(isValid());
}

bool Box3::isValid() const
{
    return m_axis[0].isUnitLength() && m_axis[1].isUnitLength() && m_axis[2].isUnitLength() &&
        m_extent[0] >= 0.0f && m_extent[1] >= 0.0f && m_extent[2] >= 0.0f &&
        std::abs(m_axis[0].dot(m_axis[1])) <= FloatCompare::ZERO_TOLERANCE &&
        std::abs(m_axis[0].dot(m_axis[2])) <= FloatCompare::ZERO_TOLERANCE &&
        std::abs(m_axis[1].dot(m_axis[2])) <= FloatCompare::ZERO_TOLERANCE;
}

Vector3 Box3::center() const
{
    return m_center;
}

void Box3::center(const Vector3& center)
{
    m_center = center;
}

Vector3 Box3::axis(unsigned index) const
{
    assert(index <= 2);
    return m_axis[index];
}

void Box3::axis(const std::array<Vector3, 3>& axis)
{
    assert(axis[0].isUnitLength() && axis[1].isUnitLength() && axis[2].isUnitLength() &&
        std::abs(axis[0].dot(axis[1])) <= FloatCompare::ZERO_TOLERANCE &&
        std::abs(axis[0].dot(axis[2])) <= FloatCompare::ZERO_TOLERANCE &&
        std::abs(axis[1].dot(axis[2])) <= FloatCompare::ZERO_TOLERANCE);
    m_axis = axis;
}

float Box3::extent(unsigned index) const
{
    assert(index <= 2);
    return m_extent[index];
}

void Box3::extent(unsigned index, float extent)
{
    assert(index <= 2);
    assert(extent >= 0.0f);
    m_extent[index] = extent;
}

std::array<Vector3, 8> Box3::computeVertices() const
{
    std::array<Vector3, 8> vertices;
    const Vector3 product0 = m_extent[0] * m_axis[0];
    const Vector3 product1 = m_extent[1] * m_axis[1];
    const Vector3 product2 = m_extent[2] * m_axis[2];
    vertices[0] = m_center - product0 - product1 - product2;
    vertices[1] = m_center + product0 - product1 - product2;
    vertices[2] = m_center + product0 + product1 - product2;
    vertices[3] = m_center - product0 + product1 - product2;
    vertices[4] = m_center - product0 - product1 + product2;
    vertices[5] = m_center + product0 - product1 + product2;
    vertices[6] = m_center + product0 + product1 + product2;
    vertices[7] = m_center - product0 + product1 + product2;
    return vertices;
}

Box3 Box3::swapToMajorAxis() const
{
    std::array<Vector3, 3> axis = m_axis;
    std::array<float, 3> extent = m_extent;
    // 將m_axis 0,1,2調整到主要為x,y,z
    if (m_axis[1].x() * m_axis[1].x() > m_axis[0].x() * m_axis[0].x())
    {
        // y <--> x
        axis[0] = m_axis[1];
        axis[1] = m_axis[0];
        extent[0] = m_extent[1];
        extent[1] = m_extent[0];
    }
    if (m_axis[2].x() * m_axis[2].x() > m_axis[0].x() * m_axis[0].x())
    {
        // z <--> x
        axis[0] = m_axis[2];
        axis[2] = m_axis[0];
        extent[0] = m_extent[2];
        extent[2] = m_extent[0];
    }
    if (m_axis[2].y() * m_axis[2].y() > m_axis[1].y() * m_axis[1].y())
    {
        // z <--> y
        axis[1] = m_axis[2];
        axis[2] = m_axis[1];
        extent[1] = m_extent[2];
        extent[2] = m_extent[1];
    }
    // 把軸都調整到正向
    if (axis[0].x() < 0.0f) axis[0] = -axis[0];
    if (axis[1].y() < 0.0f) axis[1] = -axis[1];
    if (axis[2].z() < 0.0f) axis[2] = -axis[2];
    // 調整正交規則
    Vector3 cross = axis[0].cross(axis[1]);
    if (cross.dot(axis[2]) < 0.0f)
    {
        axis[0] = -axis[0];
    }
    return { m_center, axis, extent };
}

bool Box3::operator== (const Box3& box) const
{
    return m_center == box.m_center && m_axis == box.m_axis &&
        FloatCompare::isEqual(m_extent[0], box.m_extent[0]) &&
        FloatCompare::isEqual(m_extent[1], box.m_extent[1]) &&
        FloatCompare::isEqual(m_extent[2], box.m_extent[2]);
}

bool Box3::operator!= (const Box3& box) const
{
    return m_center != box.m_center || m_axis != box.m_axis ||
        !FloatCompare::isEqual(m_extent[0], box.m_extent[0]) ||
        !FloatCompare::isEqual(m_extent[1], box.m_extent[1]) ||
        !FloatCompare::isEqual(m_extent[2], box.m_extent[2]);
}

bool Box3::isZero() const
{
    return m_center.isZero() && FloatCompare::isEqual(m_extent[0], 0.0f) && FloatCompare::isEqual(m_extent[1], 0.0f) && FloatCompare::isEqual(m_extent[2], 0.0f);
}

const Box3 Box3::UNIT_BOX{ Vector3{ 0.0f, 0.0f, 0.0f }, { Vector3{ 1.0f, 0.0f, 0.0f }, Vector3{ 0.0f, 1.0f, 0.0f }, Vector3{ 0.0f, 0.0f, 1.0f } }, { 0.5f, 0.5f, 0.5f } };