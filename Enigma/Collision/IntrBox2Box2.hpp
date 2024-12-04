/*********************************************************************
 * \file   IntrBox2Box2.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   December 2024
 *********************************************************************/
#ifndef INTR_BOX2_BOX2_HPP
#define INTR_BOX2_BOX2_HPP
#include "Intersector.hpp"
#include "Math/Box2.hpp"

namespace Collision
{
    class IntrBox2Box2 final : public Intersector
    {
    public:
        IntrBox2Box2(const Math::Box2& box0, const Math::Box2& box1);

        [[nodiscard]] const Math::Box2& box0() const;
        [[nodiscard]] const Math::Box2& box1() const;

        bool test() override;

    private:
        Math::Box2 m_box0;
        Math::Box2 m_box1;
    };
}

#endif // INTR_BOX2_BOX2_HPP
