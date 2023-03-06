export module Math:Vec4;
import <cstdio>;
import :Vec2;
import :Vec3;

export namespace linalg
{
    template<class T> class vec4;
    template<class T> class mat3;

    /**
     * @brief 4D vector
     * @tparam T Number representation to use
    */
    template<class T> class vec4
    {
    public:
        union
        {
            T vec[4];
            struct { T x, y, z, w; };
        };

        constexpr vec4() : vec4(0.0f) {}

        constexpr vec4(const T& value) : vec4(value, value, value, value) {}

        constexpr vec4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

        constexpr vec4(const vec3<T>& v, const T& w) : vec4(v.x, v.y, v.z, w) {}

        void set(const T& x, const T& y, const T& z, const T& w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        vec2<T> xy() const
        {
            return vec2<T>(x, y);
        }

        vec3<T> xyz() const
        {
            return vec3<T>(x, y, z);
        }

        vec4<T> operator +(const vec4<T>& v) const
        {
            return vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        vec4<T>& operator += (const vec4<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;

            return *this;
        }

        vec4<T> operator -(const vec4<T>& v) const
        {
            return vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        vec4<T> operator *(const T& s) const
        {
            return vec4<T>(x * s, y * s, z * s, w * s);
        }

        bool operator == (const vec4<T>& rhs) const;
    };
}