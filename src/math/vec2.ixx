export module Math:Vec2;

export namespace linalg
{
    /**
     * @brief 2D vector
     * @tparam T Number representation to use
    */
    template<class T>
    class vec2
    {
    public:
        union
        {
            T vec[2];
            struct { T x, y; };
        };

        /**
         * @brief Constructor: default zero initialization
        */
        constexpr vec2() : vec2(0.0f) {}

        /**
         * @brief Constuctor: value initialization.
         * @param value Value to set each element to.
        */
        constexpr vec2(const T& value) : vec2(value, value) {}

        /**
         * @brief Constructor: element initialization.
         * @param x Value for vec2::x
         * @param y Value for vec2::y
        */
        constexpr vec2(const T& x, const T& y) : x(x), y(y) {}

        /**
         * @brief Calculates the dot procuct between this and u
         * @param u Second vector in the dot product
         * @return this.x * u.x + this.y + u.y
        */
        constexpr float dot(const vec2<T>& u) const
        {
            return x * u.x + y * u.y;
        }

        /**
         * @brief Gets the length of the vector
         * @details |u| = sqrt(u.u)
         * @return length of the vector.
        */
        constexpr float length() const
        {
            return sqrt(x * x + y * y);
        }

        /**
         * @brief Gets the squared length of the vector
         * @return squared length of the vector.
        */
        constexpr float length_squared() const
        {
            return x * x + y * y;
        }

        /**
         * @brief Normalize the vector.
         * @details Formula is u/|u| = u/(u.u)
         * @return reference to this
        */
        constexpr vec2<T>& normalize()
        {
            T lengthSquared = length_squared();

            if(lengthSquared < 1e-8)
            {
                *this = vec2<T>(0.0);
            }
            else
            {
                T inormSquared = 1.0 / sqrt(lengthSquared);
                *this = vec2<T>(x * inormSquared, y * inormSquared);
            }
            return *this;
        }

        /**
         * @brief Project on v: v * u.v/v.v
        */
        constexpr vec2<T> project(vec2<T>& v) const
        {
            T vnormSquared = v.x * v.x + v.y * v.y;
            return v * (this->dot(v) / vnormSquared);
        }

        /**
         * @brief Gets the angle to v
         * @param v Target for the calculation
         * @return Angle between this and v
        */
        constexpr float angle(vec2<T>& v)
        {
            vec2<T>	un = vec2f(*this).normalize(),
                vn = vec2f(v).normalize();
            return acos(un.dot(vn));
        }

        /**
         * @brief Assignment operation
         * @param v New values for the vector
         * @return Reference to this
        */
        constexpr vec2<T>& operator =(const vec2<T>& v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        /**
         * @brief Element addition
         * @param v Vector to add
         * @return Reference to this
        */
        constexpr vec2<T>& operator +=(const vec2<T>& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        /**
         * @brief Element subtraction
         * @param v Vector to subtract
         * @return Reference to this
        */
        constexpr vec2<T>& operator -=(const vec2<T>& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        /**
         * @brief Element multiplication
         * @param s Scalar value to multiply
         * @return Reference to this
        */
        constexpr vec2<T>& operator *=(const T& s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        /**
        * @brief Element multiplication
        * @param v Vector to multiply
        * @return Reference to this
       */
        constexpr vec2<T>& operator *=(const vec2<T>& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        /**
        * @brief Element devision
        * @param v Vector to divide
        * @return Reference to this
       */
        constexpr vec2<T>& operator /=(const T& v)
        {
            x /= v;
            y /= v;
            return *this;
        }

        /**
         * @brief Invers operator
         * @return New vector representing the inverse of this.
        */
        constexpr vec2<T> operator -() const
        {
            return vec2<T>(-x, -y);
        }

        /**
         * @brief Multiplication
         * @param s Right side value
         * @return Product of this * s
        */
        constexpr vec2<T> operator *(const T& s) const
        {
            return vec2<T>(x * s, y * s);
        }

        /**
         * @brief Multiplication
         * @param v Right side value
         * @return Product of this * v
        */
        constexpr vec2<T> operator *(const vec2<T>& v) const
        {
            return vec2<T>(x * v.x, y * v.y);
        }

        /**
         * @brief Division
         * @param v Right side value
         * @return Quotient of this / v
        */
        constexpr vec2<T> operator /(const T& v) const
        {
            T iv = 1.0 / v;
            return vec2(x * iv, y * iv);
        }

        /**
         * @brief Addition
         * @param v Right side value
         * @return Sum of this + v
        */
        constexpr vec2<T> operator +(const vec2<T>& v) const
        {
            return vec2<T>(x + v.x, y + v.y);
        }

        /**
         * @brief Subtraction
         * @param v Right side value
         * @return Difference of this - v
        */
        constexpr vec2<T> operator -(const vec2<T>& v) const
        {
            return vec2<T>(x - v.x, y - v.y);
        }

        constexpr T operator %(const vec2<T>& v) const
        {
            return x * v.y - y * v.x;
        }

    };
}