#include "ColorRGB.hpp"
#include <algorithm>

using namespace Math;

constexpr auto FULL_BYTE = 255;
constexpr auto FULL_BYTE_F = 255.0f;
constexpr auto BYTE_SHIFT = 8;
constexpr auto SHORT_SHIFT = 16;
constexpr auto BYTE_MASK = 0xff;

static unsigned int rgbFloat2Int(float r, float g, float b)
{
    unsigned int rgb = static_cast<unsigned char>(r * FULL_BYTE);
    rgb = (rgb << BYTE_SHIFT) + static_cast<unsigned char>(g * FULL_BYTE);
    rgb = (rgb << BYTE_SHIFT) + static_cast<unsigned char>(b * FULL_BYTE);
    return rgb;
}

static std::array<float, 3> rgbInt2Float(unsigned int rgb)
{
    unsigned char c = rgb & BYTE_MASK;
    const float b = static_cast<float>(c) / FULL_BYTE_F;
    c = (rgb >> BYTE_SHIFT) & BYTE_MASK;
    const float g = static_cast<float>(c) / FULL_BYTE_F;
    c = (rgb >> SHORT_SHIFT) & BYTE_MASK;
    const float r = static_cast<float>(c) / FULL_BYTE_F;
    return { r, g, b };
}

ColorRGB::ColorRGB() : m_tuple(), m_rgb(0)
{
}

ColorRGB::ColorRGB(float r, float g, float b) : m_tuple({ r, g, b }), m_rgb(rgbFloat2Int(r, g, b))
{
}

ColorRGB::ColorRGB(const std::array<float, 3>& c) : m_tuple(c), m_rgb(rgbFloat2Int(c[0], c[1], c[2]))
{
}

ColorRGB::ColorRGB(unsigned rgb) : m_tuple(rgbInt2Float(rgb)), m_rgb(rgb)
{
}

ColorRGB::operator const float* () const
{
    return m_tuple.data();
}

ColorRGB::operator float* ()
{
    return m_tuple.data();
}

float ColorRGB::r() const
{
    return m_tuple[0];
}

void ColorRGB::r(float r)
{
    m_tuple[0] = r;
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
}

float ColorRGB::g() const
{
    return m_tuple[1];
}

void ColorRGB::g(float g)
{
    m_tuple[1] = g;
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
}

float ColorRGB::b() const
{
    return m_tuple[2];
}

void ColorRGB::b(float b)
{
    m_tuple[2] = b;
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
}

unsigned ColorRGB::rgb() const
{
    return m_rgb;
}

bool ColorRGB::operator==(const ColorRGB& c) const
{
    return m_rgb == c.m_rgb;
}

bool ColorRGB::operator!=(const ColorRGB& c) const
{
    return m_rgb != c.m_rgb;
}

bool ColorRGB::operator<(const ColorRGB& c) const
{
    return m_rgb < c.m_rgb;
}

bool ColorRGB::operator<=(const ColorRGB& c) const
{
    return m_rgb <= c.m_rgb;
}

bool ColorRGB::operator>(const ColorRGB& c) const
{
    return m_rgb > c.m_rgb;
}

bool ColorRGB::operator>=(const ColorRGB& c) const
{
    return m_rgb >= c.m_rgb;
}

ColorRGB ColorRGB::operator+(const ColorRGB& c) const
{
    return { m_tuple[0] + c.m_tuple[0], m_tuple[1] + c.m_tuple[1], m_tuple[2] + c.m_tuple[2] };
}

ColorRGB ColorRGB::operator-(const ColorRGB& c) const
{
    return { m_tuple[0] - c.m_tuple[0], m_tuple[1] - c.m_tuple[1], m_tuple[2] - c.m_tuple[2] };
}

ColorRGB ColorRGB::operator*(const ColorRGB& c) const
{
    return { m_tuple[0] * c.m_tuple[0], m_tuple[1] * c.m_tuple[1], m_tuple[2] * c.m_tuple[2] };
}

ColorRGB ColorRGB::operator*(float scalar) const
{
    return { m_tuple[0] * scalar, m_tuple[1] * scalar, m_tuple[2] * scalar };
}

ColorRGB& ColorRGB::operator+=(const ColorRGB& c)
{
    m_tuple[0] += c.m_tuple[0];
    m_tuple[1] += c.m_tuple[1];
    m_tuple[2] += c.m_tuple[2];
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
    return *this;
}

ColorRGB& ColorRGB::operator-=(const ColorRGB& c)
{
    m_tuple[0] -= c.m_tuple[0];
    m_tuple[1] -= c.m_tuple[1];
    m_tuple[2] -= c.m_tuple[2];
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
    return *this;
}

ColorRGB& ColorRGB::operator*=(const ColorRGB& c)
{
    m_tuple[0] *= c.m_tuple[0];
    m_tuple[1] *= c.m_tuple[1];
    m_tuple[2] *= c.m_tuple[2];
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
    return *this;
}

ColorRGB& ColorRGB::operator*=(float scalar)
{
    m_tuple[0] *= scalar;
    m_tuple[1] *= scalar;
    m_tuple[2] *= scalar;
    m_rgb = rgbFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2]);
    return *this;
}

ColorRGB ColorRGB::clamp() const
{
    return { std::clamp(m_tuple[0], 0.0f, 1.0f), std::clamp(m_tuple[1], 0.0f, 1.0f), std::clamp(m_tuple[2], 0.0f, 1.0f) };
}

ColorRGB ColorRGB::scaleByMax() const
{
    const float max = std::max({ m_tuple[0], m_tuple[1], m_tuple[2] });
    return { m_tuple[0] / max, m_tuple[1] / max, m_tuple[2] / max };
}

const ColorRGB ColorRGB::BLACK(0x000000);
const ColorRGB ColorRGB::WHITE(0xffffff);
const ColorRGB ColorRGB::INVALID(0xffffff);
const ColorRGB ColorRGB::ZERO(0x000000);

namespace Math
{
    ColorRGB operator*(float scalar, const ColorRGB& c)
    {
        return c * scalar;
    }
}