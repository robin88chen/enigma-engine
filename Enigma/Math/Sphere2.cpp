﻿#include "Sphere2.hpp"
#include "MathGlobal.hpp"
#include "Vector2.hpp"
#include <cassert>

using namespace Math;

Sphere2::Sphere2() : m_center(Point2::ZERO), m_radius(0.0f)
{
}

Sphere2::Sphere2(const Point2& center, float radius) : m_center(center), m_radius(radius)
{
    assert(radius >= 0.0f);
}

Point2 Sphere2::center() const
{
    return m_center;
}

void Sphere2::center(const Point2& center)
{
    m_center = center;
}

float Sphere2::radius() const
{
    return m_radius;
}

void Sphere2::radius(float radius)
{
    assert(radius >= 0.0f);
    m_radius = radius;
}

bool Sphere2::operator== (const Sphere2& sphere) const
{
    return m_center == sphere.m_center && FloatCompare::isEqual(m_radius, sphere.m_radius);
}

bool Sphere2::operator!= (const Sphere2& sphere) const
{
    return m_center != sphere.m_center || !FloatCompare::isEqual(m_radius, sphere.m_radius);
}

bool Sphere2::contains(const Point2& point) const
{
    const float sqr_length = (point - m_center).squaredLength();
    const float sqr_radius = m_radius * m_radius;
    return sqr_length <= sqr_radius + FloatCompare::tolerance(sqr_length, sqr_radius);
}
