export module Math:Mat3;
import :Vec3;
import <ostream>;
import <cstdio>;
import <cassert>;
import <cmath>;

export namespace linalg
{
    /**
     * @brief 3D column-major matrix
     * @tparam T Number representation to use
     *
     @verbatim
     Column order
     | m11 m12 m13|
     | m21 m22 m23|
     | m31 m32 m33|
     @endverbatim
    */
    template<class T> class mat3
    {
    public:
        union
        {
            T array[9];
            T mat[3][3];
            struct { T m11, m21, m31, m12, m22, m32, m13, m23, m33; };
            struct { vec3<T> col[3]; };
        };

        mat3() {}

        //
        // row-major per-element constructor
        //
        mat3(const T& _m11, const T& _m12, const T& _m13,
            const T& _m21, const T& _m22, const T& _m23,
            const T& _m31, const T& _m32, const T& _m33)
        {
            m11 = _m11; m12 = _m12; m13 = _m13;
            m21 = _m21; m22 = _m22; m23 = _m23;
            m31 = _m31; m32 = _m32; m33 = _m33;
        }

        //
        // constructor: equal diagonal elements
        //
        mat3(const T& d) : mat3(d, d, d) {}

        //
        // constructor: diagonal elements (scaling matrix)
        //
        mat3(const T& d0, const T& d1, const T& d2)
        {
            m11 = d0;
            m22 = d1;
            m33 = d2;
            m12 = m13 = m21 = m23 = m31 = m32 = 0.0;
        }

        //
        // from basis vectors
        //
        mat3(const vec3<T>& e0, const vec3<T>& e1, const vec3<T>& e2)
        {
            col[0] = e0;
            col[1] = e1;
            col[2] = e2;
        }

        vec3<T> column(int i)
        {
            assert(i < 3);
            return col[i];
        }

        //
        // Rotation theta around vector u=(x,y,z) (Euler angle & Euler axis)
        //
        //             | 0  -z  y |
        // Ru(theta) = | z   0 -x | sin(theta) + (I - u.u^T)cos(theta) + u.u^T
        //             | -y  x  0 |
        //
        // http://en.wikipedia.org/wiki/Rotation_representation#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle
        // https://en.wikipedia.org/wiki/Rotation_matrix#Nested_dimensions
        //
        // notes: u should be normalized
        //
        static mat3<T> rotation(const T& theta, const T& x, const T& y, const T& z)
        {
            mat3<T> R;
            T c1 = std::cos(theta);
            T c2 = 1.0 - c1;
            T s = std::sin(theta);

            R.m11 = c1 + c2 * x * x;	R.m12 = c2 * x * y - s * z;	R.m13 = c2 * x * z + s * y;
            R.m21 = c2 * x * y + s * z;	R.m22 = c1 + c2 * y * y;	R.m23 = c2 * y * z - s * x;
            R.m31 = c2 * x * z - s * y;	R.m32 = c2 * y * z + s * x;	R.m33 = c1 + c2 * z * z;

            return R;
        }

        void transpose()
        {
            std::swap(m21, m12);
            std::swap(m31, m13);
            std::swap(m32, m23);
        }

        // 
        // inverse: A^(-1) = 1/det(A) * adjugate(A)
        //
        mat3<T> inverse() const
        {
            T det = determinant();
            assert(det > 1e-8);
            T idet = 1.0 / det;

            mat3<T> M;
            M.m11 = (m22 * m33 - m32 * m23);
            M.m21 = -(m21 * m33 - m31 * m23);
            M.m31 = (m21 * m32 - m31 * m22);

            M.m12 = -(m12 * m33 - m32 * m13);
            M.m22 = (m11 * m33 - m31 * m13);
            M.m32 = -(m11 * m32 - m31 * m12);

            M.m13 = (m12 * m23 - m22 * m13);
            M.m23 = -(m11 * m23 - m21 * m13);
            M.m33 = (m11 * m22 - m21 * m12);

            return M * idet;
        }

        void set(const mat3<T>& m)
        {
            col[0] = m.col[0];
            col[1] = m.col[1];
            col[2] = m.col[2];
        }

        T determinant() const
        {
            return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
        }

        //
        // (ugly) matrix normalization
        //
        void normalize();

        mat3<T> operator * (const T& s) const
        {
            return mat3<T>(m11 * s, m12 * s, m13 * s,
                m21 * s, m22 * s, m23 * s,
                m31 * s, m32 * s, m33 * s);
        }

        mat3<T> operator +(const mat3<T>& m) const
        {
            return mat3<T>(m11 + m.m11, m12 + m.m12, m13 + m.m13,
                m21 + m.m21, m22 + m.m22, m23 + m.m23,
                m31 + m.m31, m32 + m.m32, m33 + m.m33);
        }

        mat3<T> operator -(const mat3<T>& m) const
        {
            return mat3(m11 - m.m11, m12 - m.m12, m13 - m.m13,
                m21 - m.m21, m22 - m.m22, m23 - m.m23,
                m31 - m.m31, m32 - m.m32, m33 - m.m33);
        }

        mat3<T>& operator +=(const mat3<T>& m)
        {
            col[0] += m.col[0];
            col[1] += m.col[1];
            col[2] += m.col[2];

            return *this;
        }

        mat3<T>& operator *=(const T& s)
        {
            col[0] *= s;
            col[1] *= s;
            col[2] *= s;

            return *this;
        }

        mat3<T> operator *(const mat3<T>& m) const
        {
            return mat3<T>(m11 * m.m11 + m12 * m.m21 + m13 * m.m31, m11 * m.m12 + m12 * m.m22 + m13 * m.m32, m11 * m.m13 + m12 * m.m23 + m13 * m.m33,
                m21 * m.m11 + m22 * m.m21 + m23 * m.m31, m21 * m.m12 + m22 * m.m22 + m23 * m.m32, m21 * m.m13 + m22 * m.m23 + m23 * m.m33,
                m31 * m.m11 + m32 * m.m21 + m33 * m.m31, m31 * m.m12 + m32 * m.m22 + m33 * m.m32, m31 * m.m13 + m32 * m.m23 + m33 * m.m33);
        }

        vec3<T> operator *(const vec3<T>& v) const;

        //
        // thread safe debug print
        //
        void debugPrint()
        {
            std::printf("%f %f %f\n%f %f %f\n%f %f %f\n",
                m11, m12, m13, m21, m22, m23, m31, m32, m33);
        }
    };

    /**
     * @brief Prints a mat3 to the output given in out.
     * @tparam T Number type of the matrix
     * @param out ostream to send the printout.
     * @param m mat3 to print,
     * @note This function does not guarantee thread safety of the print.
     * @return out, used for chaining of operators.
    */
    template<class T>
    inline std::ostream& operator<< (std::ostream& out, const mat3<T>& m)
    {
        for(int i = 0; i < 3; i++)
            std::printf("%1.4f, %1.4f, %1.4ff\n", m.mat[0][i], m.mat[1][i], m.mat[2][i]);

        return out;
    }
}