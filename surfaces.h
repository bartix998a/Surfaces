#ifndef Z7_SURFACES_H
#define Z7_SURFACES_H

#include "real.h"
#include <functional>
#include <cmath>
#include <ostream>

namespace Surfaces_details
{
    /*
     * Compose is implementod via a struct in order to allow partial template
     * specialization.
     */
    template <typename... Fs>
    struct compose_details
    {
        static auto compose(Fs... fs)
        {
            return [=](auto p)
            {
                compose_details<Fs...>::compose(fs...)(f(p));
            };
        }
    };

    template <typename F_1, typename... Fs>
    struct compose_details<F_1, Fs...>
    {
        static auto compose(F_1 f, Fs... fs)
        {
            return [=](auto p)
            {
                return compose_details<Fs...>::compose(fs...)(f(p));
            };
        }
    };

    template <typename F>
    struct compose_details<F>
    {
        static auto compose(F f)
        {
            return f;
        }
    };

    template <>
    struct compose_details<>
    {
        static auto compose()
        {
            return [=](auto p)
            { 
                return p; 
            };
        }
    };
}

struct Point
{
    const Real x;
    const Real y;
    Point() = delete;
    Point(double x, double y) : x(x), y(y) {};

    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << p.x << " " << p.y;
        return os;
    }
};

using Surface = std::function<Real(Point)>;

inline Surface plain() noexcept
{
    return [](Point) noexcept -> Real
    { 
        return 0.0;
    };
}

inline Surface slope() noexcept
{
    return [](Point p) noexcept -> Real
    {
        return p.x;
    };
}

inline Surface steps(Real s = 1) noexcept
{
    return [=](Point p) noexcept -> Real
    {
        return (s <= 0.0) ? 0.0 : (std::floor(p.x / s));
    };
}

inline Surface stripes(Real s) noexcept
{
    return [=](Point p) noexcept -> Real
    {
        return s <= 0 ? 0 : (
                p.x > 0 ? (
                        std::fmod(std::trunc(p.x / s) == (p.x / s) ? 
                            std::floor(p.x / s) : std::floor(p.x / s) + 1, 2.0)
                    ) : std::fmod(std::floor((-p.x) / s), 2.0)
            );
    };
}

inline Surface checker(Real s = 1) noexcept
{
    return [=](Point p) noexcept -> Real
    {
        return s <= 0.0 ? 0.0 : std::fmod(stripes(s)(Point(-p.x, -p.y)) + 
                                stripes(s)(Point(-p.y, -p.x)) + 1, 2.0);
    };
}

inline Surface sqr() noexcept
{
    return [](Point p) noexcept -> Real
    {
        return p.x * p.x;
    };
}

inline Surface sin_wave() noexcept
{
    return [](Point p) noexcept -> Real
    {
        return std::sin(p.x);
    };
}

inline Surface cos_wave() noexcept
{
    return [](Point p) noexcept -> Real
    {
        return std::cos(p.x);
    };
}

inline Surface rings(Real s = 1) noexcept 
{
    return [=](Point p) noexcept -> Real
    {
        return s <= 0 ? 0.0 : ((p.x == 0 && p.y == 0) ? 1.0 : 
                                stripes(s)(Point(
                                        std::sqrt(p.x * p.x + p.y * p.y),
                                                0.0)));
    };
}

inline Surface ellipse(Real a = 1, Real b = 1) noexcept
{
    return [=](Point p) noexcept -> Real
    {
        return (a <= 0.0 || b <= 0.0) ? 0.0 : 
                (((p.x * p.x) / (a * a)) 
                + ((p.y * p.y) / (b * b))) <= 1.0 ? 1.0 : 0.0;
    };
}

inline Surface rectangle(Real a = 1, Real b = 1) noexcept
{
    return [=](Point p) noexcept -> Real
    {
        return (a <= 0.0 || b <= 0.0) ? 0.0 : 
                (-a <= p.x && p.x <= a && -b <= p.y && p.y <= b ? 1.0 : 0.0);
    };
}

inline Surface rotate(Surface f, Real deg) noexcept
{
    Real radians = (deg / 180.0) * std::numbers::pi;
    return [=](Point p) -> Real
    {
        return f(Point(p.x * std::cos(radians) + p.y * std::sin(radians),
                       p.y * std::cos(radians) - p.x * std::sin(radians)));
    };
}

inline Surface translate(Surface f, Point v) noexcept
{
    return [=](Point p) -> Real
    {
        return f(Point(p.x - v.x, p.y - v.y));
    };
}

inline Surface scale(Surface f, Point s) noexcept
{
    return [=](Point p) -> Real
    {
        return s.x == 0 || s.y == 0 ? 
                INFINITY : f(Point(p.x / s.x, p.y / s.y));
    };
}

inline Surface invert(Surface f) noexcept
{
    return [=](Point p) -> Real
    {
        return f(Point(p.y, p.x));
    };
}

inline Surface flip(Surface f) noexcept
{
    return [=](Point p) -> Real
    {
        return f(Point(-p.x, p.y));
    };
}

inline Surface mul(Surface f, Real c) noexcept
{
    return [=](Point p) -> Real
    {
        return f(p) * c;
    };
}

inline Surface add(Surface f, Real c) noexcept
{
    return [=](Point p) -> Real
    {
        return f(p) + c;
    };
}

template <typename H>
inline auto evaluate(H h) noexcept
{
    return [=](Point)
    {
        return h();
    };
}

template <typename H, typename F_1, typename... F>
inline auto evaluate(H h, F_1 f_1, F... f) noexcept
{
    return [=](Point p)
    {
        return h(f_1(p), f(p)...);
    };
}

template <typename... F>
inline auto compose(F... fs) 
{
    return Surfaces_details::compose_details<F...>::compose(fs...);
}

#endif // Z7_SURFACES_H
