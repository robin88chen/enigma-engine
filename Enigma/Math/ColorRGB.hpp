/*********************************************************************
 * \file   ColorRGB.hpp
 * \brief
 *
 * \author Lancelot 'Robin' Chen
 * \date   November 2024
 *********************************************************************/
#ifndef COLOR_RGB_HPP
#define COLOR_RGB_HPP
#include <array>
namespace Math
{
    /** Color RGB Class
    @remarks
    The components must be >= 0.
    */
    class ColorRGB
    {
    public:
        ColorRGB(); ///< initial values (0,0,0)
        ColorRGB(float r, float g, float b);
        /// index -- 0: red, 1: green, 2: blue
        ColorRGB(const std::array<float, 3>& c);
        /// rgb = 0x00rrggbb
        ColorRGB(unsigned rgb);

        operator const float* () const;
        operator float* ();
        [[nodiscard]] float r() const;
        void r(float r);
        [[nodiscard]] float g() const;
        void g(float g);
        [[nodiscard]] float b() const;
        void b(float b);
        [[nodiscard]] unsigned rgb() const;

        bool operator==(const ColorRGB& c) const;
        bool operator!=(const ColorRGB& c) const;
        bool operator<(const ColorRGB& c) const;
        bool operator<=(const ColorRGB& c) const;
        bool operator>(const ColorRGB& c) const;
        bool operator>=(const ColorRGB& c) const;

        ColorRGB operator+(const ColorRGB& c) const;
        ColorRGB operator-(const ColorRGB& c) const;
        ColorRGB operator*(const ColorRGB& c) const;
        ColorRGB operator*(float scalar) const;

        ColorRGB& operator+=(const ColorRGB& c);
        ColorRGB& operator-=(const ColorRGB& c);
        ColorRGB& operator*=(const ColorRGB& c);
        ColorRGB& operator*=(float scalar);

        // Transform the color channels to [0,1].  Clamp sets negative values to
        // zero and values larger than one to one.  ScaleByMax assumes the color
        // channels are nonnegative, finds the maximum color channel, and divides
        // all channels by that value.
        /** Transform the color channels to [0,1].
        Clamp sets negative values to zero and values larger than one to one. */
        [[nodiscard]] ColorRGB clamp() const;
        /** Transform the color channels to [0,1].
        ScaleByMax assumes the color channels are nonnegative, finds the maximum color channel, and divides
         all channels by that value. */
        [[nodiscard]] ColorRGB scaleByMax() const;

        static const ColorRGB BLACK; ///< = (0,0,0)
        static const ColorRGB WHITE; ///< = (1,1,1)
        static const ColorRGB ZERO; ///< = (0,0,0)

    private:
        std::array<float, 3> m_tuple;
        unsigned m_rgb;
    };

    /** scalar * color */
    ColorRGB operator*(float scalar, const ColorRGB& c);
}

#endif // COLOR_RGB_HPP
