/*********************************************************************
 * \file   ColorRGBA.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef COLOR_RGBA_HPP
#define COLOR_RGBA_HPP
#include <array>
#include <cstddef>
namespace Math
{
    /** Color RGB Class
    @remarks
    The components must be >= 0.
    */
    class ColorRGBA
    {
    public:
        // Construction.  The components must be >= 0.
        // For accessing of colors by array index, the map is 0 = red, 1 = green,
        // 2 = blue and 3 = alpha
        ColorRGBA(); ///< initial values (0,0,0,0)
        ColorRGBA(float r, float g, float b, float a);
        /// index -- 0: red, 1: green, 2: blue, 3: alpha
        ColorRGBA(const std::array<float, 4>& c);
        /// rgb = 0x00rrggbb
        ColorRGBA(unsigned rgb, std::byte a);

        operator const float* () const;
        operator float* ();
        [[nodiscard]] float r() const;
        void r(float r);
        [[nodiscard]] float g() const;
        void g(float g);
        [[nodiscard]] float b() const;
        void b(float b);
        [[nodiscard]] float a() const;
        void a(float a);
        [[nodiscard]] unsigned argb() const;
        [[nodiscard]] unsigned rgba() const;

        bool operator==(const ColorRGBA& c) const;
        bool operator!=(const ColorRGBA& c) const;
        bool operator<(const ColorRGBA& c) const;
        bool operator<=(const ColorRGBA& c) const;
        bool operator>(const ColorRGBA& c) const;
        bool operator>=(const ColorRGBA& c) const;

        ColorRGBA operator+(const ColorRGBA& c) const;
        ColorRGBA operator-(const ColorRGBA& c) const;
        ColorRGBA operator*(const ColorRGBA& c) const;
        ColorRGBA operator*(float scalar) const;

        ColorRGBA& operator+=(const ColorRGBA& c);
        ColorRGBA& operator-=(const ColorRGBA& c);
        ColorRGBA& operator*=(const ColorRGBA& c);
        ColorRGBA& operator*=(float scalar);

        // Transform the color channels to [0,1].  Clamp sets negative values to
        // zero and values larger than one to one.  ScaleByMax assumes the color
        // channels are nonnegative, finds the maximum color channel, and divides
        // all channels by that value.
        /** Transform the color channels to [0,1].
        Clamp sets negative values to zero and values larger than one to one. */
        [[nodiscard]] ColorRGBA clamp() const;
        /** Transform the color channels to [0,1].
        ScaleByMax assumes the color channels are nonnegative, finds the maximum color channel, and divides
        all channels by that value. */
        [[nodiscard]] ColorRGBA scaleByMax() const;

        static const ColorRGBA BLACK; ///< = (0,0,0,1)
        static const ColorRGBA WHITE; ///< = (1,1,1,1)
        static const ColorRGBA ZERO; ///< = (0,0,0,0)

    private:
        std::array<float, 4> m_tuple;
        unsigned int m_argb; // 0xaarrggbb
    };

    ColorRGBA operator*(float scalar, const ColorRGBA& c);
}

#endif // COLOR_RGBA_HPP
