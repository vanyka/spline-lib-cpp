#pragma once

namespace vanyka{

template<class T>
struct Vector2 {
    T x, y;

    T Length() const { return std::sqrt(x * x + y * y); }
    Vector2 operator-() const;
};

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
inline bool operator==(const Vector2<T>& l, const Vector2<T>& r) {
    return l.x == r.x && l.y == r.y;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
    return os << '(' << v.x << ", " << v.y << ')';
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

} // vanyka