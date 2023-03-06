export module Math:Algorithms;
import :Vec2;
import :Vec3;
import :Vec4;
import :Mat2;
import :Mat3;
import :Mat4;
import <ostream>;

export namespace linalg
{
    template<class T>
    inline std::ostream& operator<< (std::ostream& out, const vec2<T>& v)
    {
        return out << "(" << v.x << ", " << v.y << ")";
    }

    template<class T>
    inline std::ostream& operator<< (std::ostream& out, const vec3<T>& v)
    {
        return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    }

    template<>
    inline bool vec4<unsigned>::operator == (const vec4<unsigned>& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    template<class T>
    inline T dot(const vec3<T>& u, const vec3<T>& v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }

    template<class T>
    inline T dot(const vec4<T>& u, const vec4<T>& v)
    {
        return u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w;
    }

    template<class T>
    inline vec3<T> normalize(const vec3<T>& u)
    {
        T length = u.length_squared();

        if(length < 1.0e-8)
            return vec3<T>(0.0, 0.0, 0.0);
        else
            return u * (T)(1.0 / sqrt(length));
    }

    template<class T>
    inline vec4<T> normalize(const vec4<T>& u)
    {
        T length = u.x * u.x + u.y * u.y + u.z * u.z + u.w * u.w;

        if(length < 1.0e-8)
            return vec4<T>(0.0, 0.0, 0.0, 0.0);
        else
            return u * (1.0 / sqrt(length));
    }

    template<class T>
    inline std::ostream& operator << (std::ostream& out, const vec4<T>& v)
    {
        return out << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    }

    template <class T>
    vec4<T> vec3<T>::xyz0() const
    {
        return vec4<T>(x, y, z, 0.0);
    }
    // explicit template specialisation for <float>
    template vec4<float> vec3<float>::xyz0() const;

    template <class T>
    vec4<T> vec3<T>::xyz1() const
    {
        return vec4<T>(x, y, z, 1.0);
    }
    // explicit template specialisation for <float>
    template vec4<float> vec3<float>::xyz1() const;

    //
    // row vector * matrix = row vector
    //
    template <class T>
    vec3<T> vec3<T>::operator *(const mat3<T>& m) const
    {
        return vec3<T>(x * m.m11 + y * m.m21 + z * m.m31,
            x * m.m12 + y * m.m22 + z * m.m32,
            x * m.m13 + y * m.m23 + z * m.m33);
    }
    // explicit template specialisation for <float>
    template vec3<float> vec3<float>::operator *(const mat3<float>& m) const;

    //
    //                | a |             | ad ae af |
    // outer product: | b | | d e f | = | bd be bf |
    //                | c |             | cd ce cf |
    //
    template <class T>
    mat3<T> vec3<T>::outer_product(const vec3<T>& v) const
    {
        return mat3<T>(*this * v.x, *this * v.y, *this * v.z);
    }
    // explicit template specialisation for <float>
    template mat3<float> vec3<float>::outer_product(const vec3<float>& v) const;

    template <class T>
    vec2<T> mat2<T>::operator*(const vec2<T>& rhs) const
    {
        return vec2<T>(m11 * rhs.x + m12 * rhs.y, m21 * rhs.x + m22 * rhs.y);
    }
    // explicit template specialisation for <float>
    template vec2<float> mat2<float>::operator*(const vec2<float>& rhs) const;

    template <class T>
    void mat3<T>::normalize()
    {
        vec3<T> r2 = vec3<T>(m12, m22, m23), r3 = vec3<T>(m13, m23, m33);
        r3.normalize();
        vec3<T> r1 = r2 % r3;
        r1.normalize();
        r2 = r3 % r1;
        m11 = r1.x; m12 = r2.x; m13 = r3.x;
        m21 = r1.y; m22 = r2.y; m23 = r3.y;
        m31 = r1.z; m32 = r2.z; m33 = r3.z;
    }
    // explicit template specialisation for <float>
    template void mat3<float>::normalize();

    template <class T>
    vec3<T> mat3<T>::operator*(const vec3<T>& v) const
    {
        return col[0] * v.x + col[1] * v.y + col[2] * v.z;
    }
    // explicit template specialisation for <float>
    template vec3<float> mat3<float>::operator*(const vec3<float>& v) const;

    template <class T>
    vec4<T> mat4<T>::operator *(const vec4<T>& v) const
    {
        return col[0] * v.x + col[1] * v.y + col[2] * v.z + col[3] * v.w;
    }
    // explicit template specialisation for <float>
    template vec4<float> mat4<float>::operator *(const vec4<float>& v) const;

    //!< Get closest whole integer that is smaller than or equal to x.
    template<typename T>
    constexpr T simplefloor(T x)
    {
        return ((double)((long)(x)-((x) < 0.0)));
    }

    /**
     * @brief Generates a random floating point number between min and max.
     * @param min Minimum value to randomize.
     * @param max Maximum value to randomize.
     * @return Randomized value between min and max
    */
    inline float rnd(const float& min, const float& max) { return min + (float)rand() / RAND_MAX * (max - min); }

    /**
     * @brief Linearly interpolates between a and b
     * @details Formula used is *(1.0f-x) + b*x
     * @tparam T Number representation to use.
     * @param a Start value.
     * @param b Target value.
     * @param x Interpolation value.
     * @return Value that is between a and b dependent on x.
    */
    template<typename T>
    inline T lerp(const T& a, const T& b, float x) { return a * (1.0f - x) + b * x; }

    /**
     * @brief Clamps a between min and max.
     * @tparam T Number representation to use.
     * @param a Value to be clamped.
     * @param min Minumum value.
     * @param max Maximum value.
     * @return [min <= a <= max]
    */
    template<typename T>
    inline T clamp(const T& a, const T& min, const T& max) { return std::max<T>(min, std::min<T>(max, a)); }

    template<typename T>
    inline T smoothstep(const T& x, const T& a, const T& b)
    {
        if(x < a)
            return 0.0;
        if(x >= b)
            return 1.0;

        T t = (x - a) / (b - a);
        return t * t * (3.0 - 2.0 * t);
    }

    /* handles negative numbers correclty
     */
    inline float mod(float a, float b)
    {
        const int n = (int)(a / b);
        a -= n * b;
        if(a < 0)
            a += b;

        return a;
    }

    inline float gammacorrect(const float& gamma, const float& x) { return powf(x, 1.0f / gamma); }
}