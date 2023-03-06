export module Math:Types;
import :Vec2;
import :Vec3;
import :Vec4;
import :Mat2;
import :Mat3;
import :Mat4;

export namespace linalg
{
    //!< Define for PI.
    constexpr auto fPI = 3.141592653f;

    //!< Define for floating point infinity.
    constexpr auto  fINF = 3.4028234e38;

    //!< Define for floating point negative infinity.
    constexpr auto  fNINF = -3.4028234e38;

    //!< Define for multiplication from Degrees to Radians.
    constexpr auto  fTO_RAD = (fPI / 180.0f);

    //!<Define for multiplication from Radians to Degrees.
    constexpr auto  fTO_DEG = (180.0f / fPI);

    typedef vec2<float> float2;
    typedef vec3<float> float3;
    typedef vec4<float> float4;

    typedef vec2<float> vec2f;
    typedef vec3<float> vec3f;
    typedef vec4<float> vec4f;

    typedef vec2<int> int2;
    typedef vec3<int> int3;
    typedef vec4<int> int4;

    typedef vec2<int> vec2i;
    typedef vec3<int> vec3i;
    typedef vec4<int> vec4i;

    typedef vec2<long> long2;
    typedef vec3<long> long3;
    typedef vec4<long> long4;

    typedef vec2<unsigned> unsigned2;
    typedef vec3<unsigned> unsigned3;
    typedef vec4<unsigned> unsigned4;
    typedef vec2<unsigned> vec2ui;
    typedef vec3<unsigned> vec3ui;
    typedef vec4<unsigned> vec4ui;


    //
    // compile-time instances
    //
    const vec2f vec2f_zero = vec2f(0, 0); //!< Compile-time zero initialized vec2f
    const vec3f vec3f_zero = vec3f(0, 0, 0); //!< Compile-time zero initialized vec3f
    const vec4f vec4f_zero = vec4f(0, 0, 0, 0); //!< Compile-time zero initialized vec4f

    typedef mat2<float> mat2f; //!< Type definition for a 2x2 float matrix
    typedef mat3<float> mat3f; //!< Type definition for a 3x3 float matrix
    typedef mat4<float> mat4f; //!< Type definition for a 4x4 float matrix

    const mat2f mat2f_zero = mat2f(0.0f); //!< Compile-time 2x2 zero matrix
    const mat3f mat3f_zero = mat3f(0.0f); //!< Compile-time 3x3 zero matrix
    const mat4f mat4f_zero = mat4f(0.0f); //!< Compile-time 4x4 zero matrix
    const mat2f mat2f_identity = mat2f(1.0f); //!< Compile-time 2x2 identity matrix
    const mat3f mat3f_identity = mat3f(1.0f); //!< Compile-time 3x3 identity matrix
    const mat4f mat4f_identity = mat4f(1.0f); //!< Compile-time 4x4 identity matrix
}