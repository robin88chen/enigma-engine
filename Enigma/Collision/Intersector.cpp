#include "Intersector.hpp"
#include <cassert>

using namespace Collision;

Intersector::Intersector() : m_intersectionType(IntersectionType::empty)
{
}

Intersector::IntersectionType Intersector::intersectionType() const
{
    return m_intersectionType;
}

bool Intersector::test()
{
    assert(false);
    return false;
}

bool Intersector::find()
{
    return test();
}
