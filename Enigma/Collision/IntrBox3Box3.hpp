/*********************************************************************
 * \file   IntrBox3Box3.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_BOX3_BOX3_HPP
#define INTR_BOX3_BOX3_HPP
#include "Intersector.hpp"
#include "Math/Box3.hpp"

namespace Collision
{
    class IntrBox3Box3 final : public Intersector
    {
    public:
        IntrBox3Box3(const Math::Box3& box0, const Math::Box3& box1);

        [[nodiscard]] const Math::Box3& box0() const;
        [[nodiscard]] const Math::Box3& box1() const;

        bool test() override;

    private:
        Math::Box3 m_box0;
        Math::Box3 m_box1;
    };
}

#endif // INTR_BOX3_BOX3_HPP
