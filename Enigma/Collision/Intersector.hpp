/*********************************************************************
 * \file   Intersector.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTERSECTOR_HPP
#define INTERSECTOR_HPP
#include <cstdint>
namespace Collision
{
    class Intersector
    {
    public:
        virtual ~Intersector() = default;
        Intersector(const Intersector&) = default;
        Intersector(Intersector&&) = default;
        Intersector& operator=(const Intersector&) = default;
        Intersector& operator=(Intersector&&) = default;

        /** Static intersection queries.  The default implementations return 'false'. */
        virtual bool test();

        /** Static intersection queries.  The default implementations call test() (return 'false').
         Produces a set of intersection.  The derived class is responsible for providing access to that set, since the nature
         of the set is dependent on the object types. */
        virtual bool find();

        /** Intersection Type -- information about the intersection set */
        enum class IntersectionType : std::uint8_t
        {
            empty = 0,
            point,
            segment,
            ray,
            line,
            polygon,
            plane,
            polyhedron,
            other
        };

        [[nodiscard]] IntersectionType intersectionType() const;

    protected:
        Intersector();
        IntersectionType m_intersectionType;
    };
}

#endif // INTERSECTOR_HPP
