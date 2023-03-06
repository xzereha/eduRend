export module Math:Mat2;
import :Vec2;
import <cmath>;

export namespace linalg
{
    /**
     * @brief 2D column-major matrix
     * @tparam T Number representation to use
     *
     @verbatim
     Column order
     | m11 m12 |
     | m21 m22 |
     @endverbatim
    */
    template<class T> class mat2
    {
    public:
        union
        {
            T array[4];
            T mat[2][2];
            struct { T m11, m21, m12, m22; };
            struct { vec2<T> col[2]; };
        };

        constexpr mat2() {}

        /**
         * @brief Constructor: from elements.
         * @param m11 Element [1, 1]
         * @param m12 Element [1, 2]
         * @param m21 Element [2, 1]
         * @param m22 Element [2, 2]
        */
        constexpr mat2(const T& m11, const T& m12, const T& m21, const T& m22) : m11(m11), m12(m12), m21(m21), m22(m22) {}

        /**
         * @brief Constructor: rotation matrix
         * @param rad Rotation angle
        */
        mat2(const T& rad)
        {
            T c = std::cos(rad);
            T s = std::sin(rad);
            m11 = c; m12 = -s;
            m21 = s; m22 = c;
        }

        /**
         * @brief Constructor: scaling matrix
         * @param scale_x Scale along x-axis
         * @param scale_y Scale along y-axis
        */
        mat2(const T& scale_x, const T& scale_y)
        {
            m11 = scale_x;	m12 = 0.0;
            m21 = 0.0;		m22 = scale_y;
        }

        mat2<T> invert() const
        {
            T det = m11 * m22 - m12 * m21;

            return mat2<T>(m22, -m21, -m12, m11) * (1.0 / det);
        }

        mat2<T> operator - ()
        {
            return mat2<T>(-m11, -m12, -m21, -m22);
        }

        mat2<T> operator * (const T& s) const
        {
            return mat2<T>(m11 * s, m12 * s, m21 * s, m22 * s);
        }

        vec2<T> operator * (const vec2<T>& rhs) const;

    };
}