#include "ColorRGBA.hpp"
#include "MathGlobal.hpp"
#include <algorithm>
#include <cassert>

using namespace Math;

constexpr auto FULL_BYTE = 255;
constexpr auto FULL_BYTE_F = 255.0f;
constexpr auto BYTE_SHIFT = 8;
constexpr auto SHORT_SHIFT = 16;
constexpr auto THREE_BYTE_SHIFT = 24;
constexpr auto BYTE_MASK = 0xff;

static unsigned int rgbaFloat2Int(float r, float g, float b, float a)
{
    assert(r >= 0.0f && g >= 0.0f && b >= 0.0f && a >= 0.0f);
    unsigned int argb = static_cast<unsigned char>(a * FULL_BYTE);
    argb = (argb << BYTE_SHIFT) + static_cast<unsigned char>(r * FULL_BYTE);
    argb = (argb << BYTE_SHIFT) + static_cast<unsigned char>(g * FULL_BYTE);
    argb = (argb << BYTE_SHIFT) + static_cast<unsigned char>(b * FULL_BYTE);
    return argb;
}

static std::array<float, 4> rgbaInt2Float(unsigned int argb)
{
    unsigned char c = argb & BYTE_MASK;
    const float b = static_cast<float>(c) / FULL_BYTE_F;
    c = (argb >> BYTE_SHIFT) & BYTE_MASK;
    const float g = static_cast<float>(c) / FULL_BYTE_F;
    c = (argb >> SHORT_SHIFT) & BYTE_MASK;
    const float r = static_cast<float>(c) / FULL_BYTE_F;
    c = (argb >> THREE_BYTE_SHIFT) & BYTE_MASK;
    const float a = static_cast<float>(c) / FULL_BYTE_F;
    return { r, g, b, a };
}

ColorRGBA::ColorRGBA() : m_tuple(), m_argb(0)
{
}

ColorRGBA::ColorRGBA(float r, float g, float b, float a) : m_tuple({ r, g, b, a }), m_argb(rgbaFloat2Int(r, g, b, a))
{
    assert(r >= 0.0f && g >= 0.0f && b >= 0.0f && a >= 0.0f);
}

ColorRGBA::ColorRGBA(const std::array<float, 4>& c) : m_tuple(c), m_argb(rgbaFloat2Int(c[0], c[1], c[2], c[3]))
{
    assert(c[0] >= 0.0f && c[1] >= 0.0f && c[2] >= 0.0f && c[3] >= 0.0f);
}

ColorRGBA::ColorRGBA(unsigned rgb, std::byte a) : m_tuple{}
{
    const unsigned argb = (static_cast<unsigned>(a) << THREE_BYTE_SHIFT) + rgb;
    m_tuple = rgbaInt2Float(argb);
    m_argb = argb;
}

ColorRGBA::operator const float* () const
{
    return m_tuple.data();
}

ColorRGBA::operator float* ()
{
    return m_tuple.data();
}

float ColorRGBA::r() const
{
    return m_tuple[0];
}

void ColorRGBA::r(float r)
{
    assert(r >= 0.0f);
    m_tuple[0] = r;
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
}

float ColorRGBA::g() const
{
    return m_tuple[1];
}

void ColorRGBA::g(float g)
{
    assert(g >= 0.0f);
    m_tuple[1] = g;
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
}

float ColorRGBA::b() const
{
    return m_tuple[2];
}

void ColorRGBA::b(float b)
{
    assert(b >= 0.0f);
    m_tuple[2] = b;
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
}

float ColorRGBA::a() const
{
    return m_tuple[3];
}

void ColorRGBA::a(float a)
{
    assert(a >= 0.0f);
    m_tuple[3] = a;
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
}

unsigned ColorRGBA::argb() const
{
    assert(m_tuple[0] <= 1.0f && m_tuple[1] <= 1.0f && m_tuple[2] <= 1.0f && m_tuple[3] <= 1.0f); // r, g, b, a are in [0,1]
    return m_argb;
}

unsigned ColorRGBA::rgba() const
{
    assert(m_tuple[0] <= 1.0f && m_tuple[1] <= 1.0f && m_tuple[2] <= 1.0f && m_tuple[3] <= 1.0f); // r, g, b, a are in [0,1]
    return (m_argb << BYTE_SHIFT) + (m_argb >> THREE_BYTE_SHIFT);
}

bool ColorRGBA::operator==(const ColorRGBA& c) const
{
    return FloatCompare::isEqual(m_tuple[0], c.m_tuple[0]) && FloatCompare::isEqual(m_tuple[1], c.m_tuple[1]) && FloatCompare::isEqual(m_tuple[2], c.m_tuple[2]) && FloatCompare::isEqual(m_tuple[3], c.m_tuple[3]);
}

bool ColorRGBA::operator!=(const ColorRGBA& c) const
{
    return !(*this == c);
}

bool ColorRGBA::operator<(const ColorRGBA& c) const
{
    return m_argb < c.m_argb;
}

bool ColorRGBA::operator<=(const ColorRGBA& c) const
{
    return m_argb <= c.m_argb;
}

bool ColorRGBA::operator>(const ColorRGBA& c) const
{
    return m_argb > c.m_argb;
}

bool ColorRGBA::operator>=(const ColorRGBA& c) const
{
    return m_argb >= c.m_argb;
}

ColorRGBA ColorRGBA::operator+(const ColorRGBA& c) const
{
    return { m_tuple[0] + c.m_tuple[0], m_tuple[1] + c.m_tuple[1], m_tuple[2] + c.m_tuple[2], m_tuple[3] + c.m_tuple[3] };
}

ColorRGBA ColorRGBA::operator-(const ColorRGBA& c) const
{
    return { m_tuple[0] - c.m_tuple[0], m_tuple[1] - c.m_tuple[1], m_tuple[2] - c.m_tuple[2], m_tuple[3] - c.m_tuple[3] };
}

ColorRGBA ColorRGBA::operator*(const ColorRGBA& c) const
{
    return { m_tuple[0] * c.m_tuple[0], m_tuple[1] * c.m_tuple[1], m_tuple[2] * c.m_tuple[2], m_tuple[3] * c.m_tuple[3] };
}

ColorRGBA ColorRGBA::operator*(float scalar) const
{
    assert(scalar >= 0.0f);
    return { m_tuple[0] * scalar, m_tuple[1] * scalar, m_tuple[2] * scalar, m_tuple[3] * scalar };
}

ColorRGBA& ColorRGBA::operator+=(const ColorRGBA& c)
{
    m_tuple[0] += c.m_tuple[0];
    m_tuple[1] += c.m_tuple[1];
    m_tuple[2] += c.m_tuple[2];
    m_tuple[3] += c.m_tuple[3];
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
    return *this;
}

ColorRGBA& ColorRGBA::operator-=(const ColorRGBA& c)
{
    m_tuple[0] -= c.m_tuple[0];
    assert(m_tuple[0] >= 0.0f);
    m_tuple[1] -= c.m_tuple[1];
    assert(m_tuple[1] >= 0.0f);
    m_tuple[2] -= c.m_tuple[2];
    assert(m_tuple[2] >= 0.0f);
    m_tuple[3] -= c.m_tuple[3];
    assert(m_tuple[3] >= 0.0f);
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
    return *this;
}

ColorRGBA& ColorRGBA::operator*=(const ColorRGBA& c)
{
    m_tuple[0] *= c.m_tuple[0];
    m_tuple[1] *= c.m_tuple[1];
    m_tuple[2] *= c.m_tuple[2];
    m_tuple[3] *= c.m_tuple[3];
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
    return *this;
}

ColorRGBA& ColorRGBA::operator*=(float scalar)
{
    assert(scalar >= 0.0f);
    m_tuple[0] *= scalar;
    m_tuple[1] *= scalar;
    m_tuple[2] *= scalar;
    m_tuple[3] *= scalar;
    m_argb = rgbaFloat2Int(m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3]);
    return *this;
}

ColorRGBA ColorRGBA::clamp() const
{
    return { std::clamp(m_tuple[0], 0.0f, 1.0f), std::clamp(m_tuple[1], 0.0f, 1.0f), std::clamp(m_tuple[2], 0.0f, 1.0f), std::clamp(m_tuple[3], 0.0f, 1.0f) };
}

ColorRGBA ColorRGBA::scaleByMax() const
{
    const float max_channel = std::max({ m_tuple[0], m_tuple[1], m_tuple[2], m_tuple[3] });
    return { m_tuple[0] / max_channel, m_tuple[1] / max_channel, m_tuple[2] / max_channel, m_tuple[3] / max_channel };
}

const ColorRGBA ColorRGBA::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
const ColorRGBA ColorRGBA::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const ColorRGBA ColorRGBA::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

namespace Math
{
    ColorRGBA operator*(float scalar, const ColorRGBA& c)
    {
        return c * scalar;
    }
}