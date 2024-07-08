#pragma once

#include <iostream>

namespace vanyka{

template<class T>
struct Vector2 {
    T x, y;

    inline T LengthSquared() const { return x * x + y * y; }
    inline T Length() const { return std::sqrt(LengthSquared()); }

    Vector2 Normalized() const { return Vector2f{ x,y } / Length(); }
    Vector2<T>& Normalize() { return *this = Normalized(); }

    inline T DistanceFrom(const Vector2& v) { return Distance(*this, v); }

    inline Vector2 operator-() const;

    static const Vector2 one;
    static const Vector2 right;
    static const Vector2 left;
    static const Vector2 up;
    static const Vector2 down;

    static inline T Distance(const Vector2& v1, const Vector2& v2) { return (v2 - v1).Length(); }
};

template<class T> inline const Vector2<T> Vector2<T>::one = Vector2{ 1,1 };
template<class T> inline const Vector2<T> Vector2<T>::right = Vector2{ 1,0 };
template<class T> inline const Vector2<T> Vector2<T>::left = -right;
template<class T> inline const Vector2<T> Vector2<T>::up = Vector2{ 0,1 };
template<class T> inline const Vector2<T> Vector2<T>::down = -up;

// Operators
template<class T>
Vector2<T> Vector2<T>::operator-() const { return { -x, -y }; }

template<class T>
inline Vector2<T> operator+(const Vector2<T>& l, const Vector2<T>& r) {
    return { l.x + r.x, l.y + r.y };
}

template<class T>
inline Vector2<T> operator-(const Vector2<T>& l, const Vector2<T>& r) {
    return { l.x - r.x, l.y - r.y };
}

template<class T>
inline Vector2<T> operator*(const Vector2<T>& l, const Vector2<T>& r) {
    return { l.x * r.x, l.y * r.y };
}

template<class T>
inline Vector2<T> operator/(const Vector2<T>& l, const Vector2<T>& r) {
    return { l.x / r.x, l.y / r.y };
}

template<class T, class NumType>
inline Vector2<T> operator* (const Vector2<T>& v, const NumType& n) {
    return { v.x * n, v.y * n };
}
template<class T, class NumType>
inline Vector2<T> operator* (const NumType& n, const Vector2<T>& v) { return v * n; }

template<class T, class NumType>
inline Vector2<T> operator/ (const Vector2<T>& v, const NumType& n) {
    return { v.x / n, v.y / n };
}

template<class T>
inline Vector2<T>& operator+=(Vector2<T>& l, const Vector2<T>& r) {
    l.x += r.x; l.y += r.y;
    return l;
}

template<class T>
inline Vector2<T>& operator-=(Vector2<T>& l, const Vector2<T>& r) {
    l.x -= r.x; l.y -= r.y;
    return l;
}

template<class T>
inline Vector2<T>& operator*=(Vector2<T>& l, const Vector2<T>& r) {
    l.x *= r.x; l.y *= r.y;
    return l;
}

template<class T>
inline Vector2<T>& operator/=(Vector2<T>& l, const Vector2<T>& r) {
    l.x /= r.x; l.y /= r.y;
    return l;
}

template<class T>
inline bool operator==(const Vector2<T>& l, const Vector2<T>& r) {
    return l.x == r.x && l.y == r.y;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}

template<class T>
Vector2<T> Lerp(const Vector2<T>& v1, const Vector2<T>& v2, const float& t) 
{ return v1 + (v2 - v1) * t; }

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

} // vanyka