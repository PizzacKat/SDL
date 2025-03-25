#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <initializer_list>
#include <stdexcept>

#include "Vector.hpp"

namespace SDL {
    template <typename T = int>
    class Matrix3x3 {
    public:
        constexpr Matrix3x3()= default;
        constexpr Matrix3x3( const T a1, const T b1, const T c1,
                const T a2, const T b2, const T c2,
                const T a3, const T b3, const T c3): _data(a1, b1, c1, a2, b2, c2, a3, b3, c3) {

        }
        constexpr explicit Matrix3x3(const Vector2<T> &vec2): Matrix3x3(
                                                    vec2.x, 0, 0,
                                                    vec2.y, 0, 0,
                                                         1, 0, 0
                                                    ) {

        }
        constexpr explicit Matrix3x3(const Vector3<T> &vec3): Matrix3x3(
                                                    vec3.x, 0, 0,
                                                    vec3.y, 0, 0,
                                                    vec3.z, 0, 0
                                                    ) {

        }
        template <typename N>
        constexpr Matrix3x3(const Matrix3x3<N> &other): Matrix3x3(
                                            static_cast<T>(other._data[0]), static_cast<T>(other._data[1]), static_cast<T>(other._data[2]),
                                            static_cast<T>(other._data[3]), static_cast<T>(other._data[4]), static_cast<T>(other._data[5]),
                                            static_cast<T>(other._data[6]), static_cast<T>(other._data[7]), static_cast<T>(other._data[8])
                                            ) {

        }

        [[nodiscard]] constexpr const T &Get(const std::size_t x, const std::size_t y) const {
            if (x >= 3)
                throw std::out_of_range("x (which is " + std::to_string(x) + ") >= width (which is 3)");
            if (y >= 3)
                throw std::out_of_range("y (which is " + std::to_string(x) + ") >= height (which is 3)");
            return _data[x + y * 3];
        }

        [[nodiscard]] constexpr T &Get(const std::size_t x, const std::size_t y) {
            if (x >= 3)
                throw std::out_of_range("x (which is " + std::to_string(x) + ") >= width (which is 3)");
            if (y >= 3)
                throw std::out_of_range("y (which is " + std::to_string(x) + ") >= height (which is 3)");
            return _data[x + y * 3];
        }

        [[nodiscard]] constexpr const T &operator()(const std::size_t x, const std::size_t y) const {
            return Get(x, y);
        }

        [[nodiscard]] constexpr T &operator()(const std::size_t x, const std::size_t y) {
            return Get(x, y);
        }

        [[nodiscard]] constexpr Matrix3x3 operator+(const Matrix3x3 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0] + b[0], a[1] + b[1], a[2] + b[2],
                    a[3] + b[3], a[4] + b[4], a[5] + b[5],
                    a[6] + b[6], a[7] + b[7], a[8] + b[8]};
        }

        constexpr Matrix3x3 &operator+=(const Matrix3x3 &other) {
            return *this = *this + other;
        }

        [[nodiscard]] constexpr Matrix3x3 operator-(const Matrix3x3 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0] - b[0], a[1] - b[1], a[2] - b[2],
                    a[3] - b[3], a[4] - b[4], a[5] - b[5],
                    a[6] - b[6], a[7] - b[7], a[8] - b[8]};
        }

        constexpr Matrix3x3 &operator-=(const Matrix3x3 &other) {
            return *this = *this - other;
        }

        [[nodiscard]] constexpr Matrix3x3 operator*(const Matrix3x3 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0] * b[0] + a[1] * b[3] + a[2] * b[6], a[0] * b[1] + a[1] * b[4] + a[2] * b[7], a[0] * b[2] + a[1] * b[5] + a[2] * b[8],
                    a[3] * b[0] + a[4] * b[3] + a[5] * b[6], a[3] * b[1] + a[4] * b[4] + a[5] * b[7], a[3] * b[2] + a[4] * b[5] + a[5] * b[8],
                    a[6] * b[0] + a[7] * b[3] + a[8] * b[6], a[6] * b[1] + a[7] * b[4] + a[8] * b[7], a[6] * b[2] + a[7] * b[5] + a[8] * b[8]};
        }

        constexpr Matrix3x3 &operator*=(const Matrix3x3 &other) {
            return *this = *this * other;
        }

        [[nodiscard]] constexpr Matrix3x3 operator*(const T &other) const {
            const T *a = _data;
            const T &b = other;
            return {a[0] * b, a[1] * b, a[2] * b,
                    a[3] * b, a[4] * b, a[5] * b,
                    a[6] * b, a[7] * b, a[8] * b};
        }

        constexpr Matrix3x3 &operator*=(const T &other) {
            return *this = *this * other;
        }

        [[nodiscard]] constexpr Matrix3x3 Transpose() const {
            const T *a = _data;
            return {a[0], a[3], a[6],
                    a[1], a[4], a[7],
                    a[2], a[5], a[8]};
        }

        [[nodiscard]] constexpr const T *Data() const {
            return _data;
        }

        constexpr explicit operator Vector3<T>() const {
            return {_data[0], _data[3], _data[6]};
        }

        constexpr explicit operator Vector2<T>() const {
            return {_data[0], _data[3]};
        }

        static inline Matrix3x3 Identity{1, 0, 0,
                                         0, 1, 0,
                                         0, 0, 1};
    private:
        T _data[3 * 3];
    };

    typedef Matrix3x3<float> FMatrix3x3;
    typedef Matrix3x3<unsigned int> UMatrix3x3;

    template <typename T = int>
    class Matrix4x4 {
    public:
        constexpr Matrix4x4()= default;
        constexpr Matrix4x4( const T a1, const T b1, const T c1, const T d1,
                const T a2, const T b2, const T c2, const T d2,
                const T a3, const T b3, const T c3, const T d3,
                const T a4, const T b4, const T c4, const T d4): _data(a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3, a4, b4, c4, d4) {

        }
        constexpr explicit Matrix4x4(const Vector3<T> &vec3): Matrix4x4(
                                            vec3.x, 0, 0, 0,
                                            vec3.y, 0, 0, 0,
                                            vec3.z, 0, 0, 0,
                                                 1, 0, 0, 0
                                            ) {

        }
        constexpr explicit Matrix4x4(const Vector4<T> &vec4): Matrix4x4(
                                            vec4.x, 0, 0, 0,
                                            vec4.y, 0, 0, 0,
                                            vec4.z, 0, 0, 0,
                                            vec4.w, 0, 0, 0
                                            ) {

        }
        template <typename N>
        constexpr Matrix4x4(const Matrix4x4<N> &other): Matrix4x4(
                                            static_cast<T>(other._data[0]), static_cast<T>(other._data[1]), static_cast<T>(other._data[2]), static_cast<T>(other._data[3]),
                                            static_cast<T>(other._data[4]), static_cast<T>(other._data[5]), static_cast<T>(other._data[6]), static_cast<T>(other._data[7]),
                                            static_cast<T>(other._data[8]), static_cast<T>(other._data[9]), static_cast<T>(other._data[10]), static_cast<T>(other._data[11]),
                                            static_cast<T>(other._data[12]), static_cast<T>(other._data[13]), static_cast<T>(other._data[14]), static_cast<T>(other._data[15])) {

        }
        constexpr Matrix4x4(const Matrix3x3<T> &mat3): _data(
                                            mat3.Data()[0], mat3.Data()[1], mat3.Data()[2], 0,
                                            mat3.Data()[3], mat3.Data()[4], mat3.Data()[5], 0,
                                            mat3.Data()[6], mat3.Data()[7], mat3.Data()[8], 0,
                                                         0,              0,              0, 0) {

        }

        [[nodiscard]] constexpr const T &Get(const std::size_t x, const std::size_t y) const {
            if (x >= 4)
                throw std::out_of_range("x (which is " + std::to_string(x) + ") >= width (which is 4)");
            if (y >= 4)
                throw std::out_of_range("y (which is " + std::to_string(x) + ") >= height (which is 4)");
            return _data[x + y * 4];
        }

        [[nodiscard]] constexpr T &Get(const std::size_t x, const std::size_t y) {
            if (x >= 4)
                throw std::out_of_range("x (which is " + std::to_string(x) + ") >= width (which is 4)");
            if (y >= 4)
                throw std::out_of_range("y (which is " + std::to_string(x) + ") >= height (which is 4)");
            return _data[x + y * 4];
        }

        [[nodiscard]] constexpr const T &operator()(const std::size_t x, const std::size_t y) const {
            return Get(x, y);
        }

        [[nodiscard]] constexpr T &operator()(const std::size_t x, const std::size_t y) {
            return Get(x, y);
        }

        [[nodiscard]] constexpr Matrix4x4 operator+(const Matrix4x4 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0]  + b[0],  a[1]  + b[1],  a[2]  + b[2],  a[3]  + b[3],
                    a[4]  + b[4],  a[5]  + b[5],  a[6]  + b[6],  a[7]  + b[7],
                    a[8]  + b[8],  a[9]  + b[9],  a[10] + b[10], a[11] + b[11],
                    a[12] + b[12], a[13] + b[13], a[14] + b[14], a[15] + b[15]
            };
        }

        constexpr Matrix4x4 &operator+=(const Matrix4x4 &other) {
            return *this = *this + other;
        }

        [[nodiscard]] constexpr Matrix4x4 operator-(const Matrix4x4 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0]  - b[0],  a[1]  - b[1],  a[2]  - b[2],  a[3]  - b[3],
                    a[4]  - b[4],  a[5]  - b[5],  a[6]  - b[6],  a[7]  - b[7],
                    a[8]  - b[8],  a[9]  - b[9],  a[10] - b[10], a[11] - b[11],
                    a[12] - b[12], a[13] - b[13], a[14] - b[14], a[15] - b[15]
            };
        }

        constexpr Matrix4x4 &operator-=(const Matrix4x4 &other) {
            return *this = *this - other;
        }

        [[nodiscard]] constexpr Matrix4x4 operator*(const Matrix4x4 &other) const {
            const T *a = _data;
            const T *b = other._data;
            return {a[0]  * b[0] + a[1]  * b[4] + a[2]  * b[8] +  a[3] * b[12], a[0]  * b[1] + a[1]  * b[5] + a[2]  * b[9] + a[3]  * b[13], a[0]  * b[2] + a[1]  * b[6] + a[2]  * b[10] + a[3]  * b[14], a[0]  * b[3] + a[1]  * b[7] + a[2]  * b[11] + a[3]  * b[15],
                    a[4]  * b[0] + a[5]  * b[4] + a[6]  * b[8] +  a[7] * b[12], a[4]  * b[1] + a[5]  * b[5] + a[6]  * b[9] + a[7]  * b[13], a[4]  * b[2] + a[5]  * b[6] + a[6]  * b[10] + a[7]  * b[14], a[4]  * b[3] + a[5]  * b[7] + a[6]  * b[11] + a[7]  * b[15],
                    a[8]  * b[0] + a[9]  * b[4] + a[10] * b[8] + a[11] * b[12], a[8]  * b[1] + a[9]  * b[5] + a[10] * b[9] + a[11] * b[13], a[8]  * b[2] + a[9]  * b[6] + a[10] * b[10] + a[11] * b[14], a[8]  * b[3] + a[9]  * b[7] + a[10] * b[11] + a[11] * b[15],
                    a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12], a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13], a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14], a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15],
            };
        }

        constexpr Matrix4x4 &operator*=(const T &other) {
            return *this = *this * other;
        }

        [[nodiscard]] constexpr const T *Data() const {
            return _data;
        }

        constexpr explicit operator Vector4<T>() const {
            return {_data[0], _data[4], _data[8], _data[12]};
        }

        constexpr explicit operator Vector3<T>() const {
            return {_data[0], _data[4], _data[8]};
        }

        static inline Matrix4x4 Identity{1, 0, 0, 0,
                                         0, 1, 0, 0,
                                         0, 0, 1, 0,
                                         0, 0, 0, 1};
    private:
        T _data[4 * 4];
    };

    typedef Matrix4x4<float> FMatrix4x4;
    typedef Matrix4x4<unsigned int> UMatrix4x4;

    template <typename T>
    constexpr Vector2<T> Apply(const Matrix3x3<T> &mat3, const Vector2<T> &vec2) {
        return static_cast<Vector2<T>>(mat3 * Matrix3x3<T>(vec2));
    }

    template <typename T>
    constexpr Vector3<T> Apply(const Matrix3x3<T> &mat3, const Vector3<T> &vec3) {
        return static_cast<Vector3<T>>(mat3 * Matrix3x3<T>(vec3));
    }

    template <typename T>
    constexpr Vector3<T> Apply(const Matrix4x4<T> &mat4, const Vector3<T> &vec3) {
        return static_cast<Vector3<T>>(mat4 * Matrix4x3<T>(vec3));
    }

    template <typename T>
    constexpr Vector4<T> Apply(const Matrix4x4<T> &mat4, const Vector4<T> &vec4) {
        return static_cast<Vector4<T>>(mat4 * Matrix4x4<T>(vec4));
    }
}

#endif //MATRIX_HPP
