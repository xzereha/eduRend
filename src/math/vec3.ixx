export module Math:Vec3;
import <cstdio>;
import <cmath>;

export namespace linalg
{

    template<class T> class vec4;
    template<class T> class mat3;

    /**
    * @brief 3D vector
    * @tparam T Number representation to use
    */
    template<class T> class vec3
    {
    public:
        union
        {
            T vec[3];
            struct { T x, y, z; };
        };

        constexpr vec3() : vec3(0.0f) {}

        constexpr vec3(const T& value) : vec3(value, value, value) {}

        constexpr vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

        vec4<T> xyz0() const;

        vec4<T> xyz1() const;

        void set(const T& x, const T& y, const T& z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        T dot(const vec3<T>& u) const
        {
            return x * u.x + y * u.y + z * u.z;
        }

        //
        // vector length (2-norm): |u| = sqrt(u.u)
        //
        constexpr T length() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        constexpr T length_squared() const
        {
            return x * x + y * y + z * z;
        }

        //
        // normalization: u/|u| = u/(u.u)
        // divide-by-zero safe
        //
        vec3<T>& normalize()
        {
            T normSquared = x * x + y * y + z * z;

            if(normSquared < 1e-8)
            {
                set(0.0, 0.0, 0.0);
            }
            else
            {
                float inormSquared = (T)(1.0 / std::sqrt(normSquared));
                set(x * inormSquared, y * inormSquared, z * inormSquared);
            }
            return *this;
        }

        //
        // project on v: v * u.v/v.v
        //
        vec3<T> project(const vec3<T>& v) const
        {
            T vnormSquared = v.x * v.x + v.y * v.y + v.z * v.z;
            return v * (this->dot(v) / vnormSquared);
        }

        //
        // angle to vector
        //
        T angle(vec3<T>& v) const
        {
            vec3<T>	un = vec3<T>(*this).normalize(),
                vn = vec3<T>(v).normalize();
            return acos(un.dot(vn));
        }

        vec3<T>& operator +=(const vec3<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        vec3<T>& operator -=(const vec3<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        vec3<T>& operator *=(const T& s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        vec3<T>& operator *=(const vec3<T>& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        vec3<T>& operator /=(const T& v)
        {
            x /= v;
            y /= v;
            z /= v;
            return *this;
        }

        vec3<T> operator -() const
        {
            return vec3<T>(-x, -y, -z);
        }

        vec3<T> operator *(const T& s) const
        {
            return vec3(x * s, y * s, z * s);
        }

        vec3<T> operator *(const vec3<T>& v) const
        {
            return vec3<T>(x * v.x, y * v.y, z * v.z);
        }

        vec3<T> operator /(const T& s) const
        {
            T is = 1.0 / s;
            return vec3<T>(x * is, y * is, z * is);
        }

        vec3<T> operator +(const vec3<T>& v) const
        {
            return vec3<T>(x + v.x, y + v.y, z + v.z);
        }

        vec3<T> operator -(const vec3<T>& v) const
        {
            return vec3<T>(x - v.x, y - v.y, z - v.z);
        }

        vec3<T> operator %(const vec3<T>& v) const
        {
            return vec3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
        }

        vec3<T> operator *(const mat3<T>& m) const;

        bool operator == (const vec3<T>& rhs) const
        {
            return x == rhs.x && y == rhs.y && z == rhs.z;
        }

        mat3<T> outer_product(const vec3<T>& v) const;

        void debugPrint() const
        {
            std::printf("(%f,%f,%f)\n", x, y, z);
        }
    };
}