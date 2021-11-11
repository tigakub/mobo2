#ifndef __MATH_HPP__
#define __MATH_HPP__

#define FLOAT_PRECISION 1e-6

#include <math.h>
#include <float.h>
#include <type_traits>
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;
using std::fixed;
using std::scientific;
using std::ios;

#define RADIANS(d) (d * (float) M_PI / 180.0f)
#define DEGREES(r) (r * 180.0 / (float) M_PI)

namespace mobo
{
    extern float COPYSIGN(float s, float t);
    extern double COPYSIGN(double s, double t);
    extern float SIN(float s);
    extern double SIN(double s);
    extern float COS(float s);
    extern double COS(double s);
    extern float TAN(float s);
    extern double TAN(double s);
    extern float ASIN(float s);
    extern double ASIN(double s);
    extern float ACOS(float s);
    extern double ACOS(double s);
    extern float ATAN2(float y, float x);
    extern double ATAN2(double y, double x);
    extern float SQRT(float s);
    extern double SQRT(double s);
    extern float ABS(float s);
    extern double ABS(double s);

    /*
    template <class T, int S>
    struct vec {
        T v[S];
    };
    */

    template <class T, unsigned int SIZE>
    struct vec {
        static T shunt;
        
        vec(T x = T(0.0), T y = T(0.0), T z = T(0.0), T w = T(0.0)) { switch(SIZE) { case 4: v[3] = w; case 3: v[2] = z; case 2: v[1] = y; case 1: v[0] = x; } }
        // vec(const T* v) { unsigned int i = SIZE; while(i--) v[i] = v[i]; }
        vec(const T iv[SIZE]) { unsigned int i = SIZE; while(i--) v[i] = iv[i]; }
        vec(const vec<T, SIZE>& iv) { unsigned int i = SIZE; while(i--) v[i] = iv[i]; }
        vec(const vec<T, SIZE-1>& iv, T s = 0.0) { unsigned int i = SIZE-1; v[i] = s; while(i--) v[i] = iv[i]; }

        T operator[](unsigned int i) const { if(i >= SIZE) return T(0.0); return v[i]; }
        T& operator[](unsigned int i) { if(i >= SIZE) return shunt; return v[i]; }

        bool operator==(const vec<T, SIZE>& iv) const { int i = SIZE; while(i--) if(ABS(v[i] - iv[i]) > FLOAT_PRECISION) return false; return true; }
        bool operator!=(const vec<T, SIZE>& iv) const { int i = SIZE; while(i--) if(ABS(v[i] - iv[i]) > FLOAT_PRECISION) return true; return false; }

        vec<T, SIZE>& operator=(const vec<T, SIZE-1>& iv) { int i = SIZE-1; v[i] = 0.0; while(i--) v[i] += iv[i]; return *this; }
        vec<T, SIZE>& operator+=(const vec<T, SIZE>& iv) { int i = SIZE; while(i--) v[i] += iv[i]; return *this; }
        vec<T, SIZE>& operator-=(const vec<T, SIZE>& iv) { int i = SIZE; while(i--) v[i] -= iv[i]; return *this; }
        vec<T, SIZE>& operator&=(const vec<T, SIZE>& iv) { int i = SIZE; while(i--) v[i] *= iv[i]; return *this; }
        vec<T, SIZE>& operator*=(T s) { int i = SIZE; while(i--) v[i] *= s; return *this; }
        vec<T, SIZE>& operator/=(T s) { s = T(1.0)/s; int i = SIZE; while(i--) v[i] *= s; return *this; }

        vec<T, SIZE> operator+(const vec<T, SIZE>& iv) const { vec<T, SIZE> r(*this); r += iv; return r; }
        vec<T, SIZE> operator-(const vec<T, SIZE>& iv) const { vec<T, SIZE> r(*this); r -= iv; return r; }
        vec<T, SIZE> operator&(const vec<T, SIZE>& iv) const { vec<T, SIZE> r(*this); r &= iv; return r; }
        vec<T, SIZE> operator*(T s) const { vec<T, SIZE> r(*this); r *= s; return r; }
        vec<T, SIZE> operator/(T s) const { s = T(1.0)/s; vec<T, SIZE> r(*this); r *= s; return r; }

        T operator*(const vec<T, SIZE>& iv) const { T r(0.0); int i = SIZE; while(i--) r += v[i] * iv[i]; return r; }

        T magSquared() const { return (*this) * (*this); }
        T mag() const { return SQRT(magSquared()); }

        vec<T, SIZE> normalized() const { T magRecip = T(1.0)/mag(); vec<T, SIZE> r(*this); r *= magRecip; return r; }

        T v[SIZE];
    };

    template <class T, unsigned int SIZE>
    T vec<T, SIZE>::shunt = T(0.0);

    template <class T> using vec2 = vec<T, 2>;
    template <class T> using vec3 = vec<T, 3>;
    template <class T> using vec4 = vec<T, 4>;

    template <class T>
    vec3<T> operator|(const vec3<T>& v1, const vec3<T> v2)
    {
        vec3<T> r;
        r[0] = v1[1] * v2[2] - v1[2] * v2[1];
        r[1] = v2[0] * v1[2] - v2[2] * v1[0];
        r[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return r;
    }

    template <class T, unsigned int SIZE>
    struct pnt {
        static T shunt;
        
        pnt(T x = T(0.0), T y = T(0.0), T z = T(0.0), T w = T(0.0)) { switch(SIZE) { case 4: v[3] = w; case 3: v[2] = z; case 2: v[1] = y; case 1: v[0] = x; } }
        pnt(const T p[SIZE]) { unsigned int i = SIZE; while(i--) v[i] = p[i]; }
        pnt(const pnt<T, SIZE>& p) { unsigned int i = SIZE; while(i--) v[i] = p[i]; }
        pnt(const pnt<T, SIZE-1>& p) { unsigned int i = SIZE-1; v[i] = 1.0; while(i--) v[i] = p[i]; }

        T operator[](unsigned int i) const { if(i >= SIZE) return T(1.0); return v[i]; }
        T& operator[](unsigned int i) { if(i >= SIZE) return shunt; return v[i]; }

        bool operator==(const vec<T, SIZE>& p) const { int i = SIZE; while(i--) if(ABS(v[i] - p[i]) > FLOAT_PRECISION) return false; return true; }
        bool operator!=(const vec<T, SIZE>& p) const { int i = SIZE; while(i--) if(ABS(v[i] - p[i]) > FLOAT_PRECISION) return true; return false; }

        pnt<T, SIZE>& operator=(const pnt<T, SIZE-1>& iv) { int i = SIZE-1; v[i] = 1.0; while(i--) v[i] += iv[i]; return *this; }
        pnt<T, SIZE>& operator=(const vec<T, SIZE-1>& iv) { int i = SIZE-1; v[i] = 1.0; while(i--) v[i] += iv[i]; return *this; }
        pnt<T, SIZE>& operator+=(const vec<T, SIZE>& iv) { int i = SIZE; while(i--) v[i] += iv[i]; return *this; }
        pnt<T, SIZE>& operator-=(const vec<T, SIZE>& iv) { int i = SIZE; while(i--) v[i] -= iv[i]; return *this; }
        pnt<T, SIZE>& operator*=(T s) { int i = SIZE; while(i--) v[i] *= s; return *this; }
        pnt<T, SIZE>& operator/=(T s) { s = T(1.0)/s; int i = SIZE; while(i--) v[i] *= s; return *this; }

        pnt<T, SIZE> operator+(const vec<T, SIZE>& iv) const { vec<T, SIZE> r(*this); r += iv; return r; }
        pnt<T, SIZE> operator-(const vec<T, SIZE>& iv) const { vec<T, SIZE> r(*this); r -= iv; return r; }
        vec<T, SIZE> operator-(const pnt<T, SIZE>& p) const { vec<T, SIZE> r; int i = SIZE; while(i--) r[i] = v[i] - p[i]; }
        pnt<T, SIZE> operator*(T s) const { pnt<T, SIZE> r(*this); r *= s; return r; }
        pnt<T, SIZE> operator/(T s) const { s = T(1.0)/s; pnt<T, SIZE> r(*this); r *= s; return r; }

        T v[SIZE];
    };

    template <class T, unsigned int SIZE>
    T pnt<T, SIZE>::shunt = T(1.0);

    template <class T> using pnt2 = pnt<T, 2>;
    template <class T> using pnt3 = pnt<T, 3>;
    template <class T> using pnt4 = pnt<T, 4>;

    typedef enum
    {
        IDENTITY = 1,
        TRANSLATION = IDENTITY + 1,
        ROTATION = TRANSLATION + 1,
        SCALING = ROTATION + 1,
        PERSPECTIVE = SCALING + 1,
        ORTHOGRAPHIC = PERSPECTIVE + 1
    } MatrixInitMode;

    template <class T>
    struct mat4 {
        
        mat4(MatrixInitMode iType = IDENTITY, T a = T(0.0), T x = T(0.0), T y = T(0.0), T z = T(0.0), T n = T(0.0), T f = T(0.0)) {
            v[15] = T(1.0);
            T factor(1.0);
            int i;
            switch(iType) {
                case SCALING:
                    factor = a;
                case IDENTITY:
                    i = 15;
                    while(i--) v[i] = factor * T((i % 5) == 0);
                    break;
                case TRANSLATION:
                    i = 15;
                    while(i--) v[i] = T((i % 5) == 0);
                    v[3] = a; v[7] = x; v[11] = y;
                    break;
                case ROTATION:
                    {
                        T c(COS(a)), s(SIN(a));
                        T cc(1 - c);
                        T xx = x * x, yy = y * y, zz = z * z;
                        T xy = x * y, xz = x * z, yz = y * z;
                        v[0] = c + xx * cc; v[1] = xy * cc - z * s; v[2] = xz * cc + y * s; v[3] = 0.0;
                        v[4] = xy * cc + z * s; v[5] = c + yy * cc; v[6] = yz * cc - x * s; v[7] = 0.0;
                        v[8] = xz * cc - y * s; v[9] = yz * cc + x * s; v[10] = c + zz * cc; v[11] = 0.0;
                        v[12] = 0.0; v[13] = 0.0; v[14] = 0.0;;
                    }
                    break;
                case PERSPECTIVE:
                    {
                        T l(a), r(x), b(y), t(z);
                        T rml(r-l), tmb(t-b), fmn(f-n);
                        T n2(n*2.0);
                        /*
                        v[0] = n2/rml; v[1] = 0.0;    v[2] = (r+l)/rml;   v[3] = 0.0;
                        v[4] = 0.0;    v[5] = n2/tmb; v[6] = (t+b)/tmb;   v[7] = 0.0;
                        v[8] = 0.0;    v[9] = 0.0;    v[10] = -(f+n)/fmn; v[11] = (n2*f)/fmn;
                        v[12] = 0.0;   v[13] = 0.0;   v[14] = -1.0;       v[15] = 0.0;
                        */
                        v[0] = n2/rml; v[1] = 0.0;    v[2] = 0.0;         v[3] = -n*(r+l)/rml;
                        v[4] = 0.0;    v[5] = n2/tmb; v[6] = 0.0;         v[7] = -n*(t+b)/tmb;
                        v[8] = 0.0;    v[9] = 0.0;    v[10] = -(f+n)/fmn; v[11] = -n2*f/fmn;
                        v[12] = 0.0;   v[13] = 0.0;   v[14] = -1.0;       v[15] = 0.0;
                        
                    }
                    break;
                case ORTHOGRAPHIC:
                    {
                        T l(a), r(x), b(y), t(z);
                        T rml(r-l), tmb(t-b), fmn(f-n);
                        v[0] = 2.0/rml; v[1] = 0.0;     v[2] = 0.0;      v[3] = (r+l)/rml;
                        v[4] = 0.0;     v[5] = 2.0/tmb; v[6] = 0.0;      v[7] = (t+b)/tmb;
                        v[8] = 0.0;     v[9] = 0.0;     v[10] = 2.0/fmn; v[11] = (f+n)/fmn;
                        v[12] = 0.0;    v[13] = 0.0;    v[14] = 0.0;     v[15] = 1.0;
                    }
                    break;
            }
        }
        mat4(const T *m) { int i = 16; while(i--) v[i] = m[i]; }
        mat4(const mat4<T>& m) { int i = 16; while(i--) v[i] = m[i]; }

        T operator[](unsigned int i) const { if(i >= 16) return T(0.0); return v[i]; }
        T& operator[](unsigned int i) { return v[i]; }

        bool operator==(const mat4<T>& m) const { int i = 16; if(ABS(v[i] - m[i]) > FLOAT_PRECISION) return false; return true; }
        bool operator!=(const mat4<T>& m) const { int i = 16; if(ABS(v[i] - m[i]) > FLOAT_PRECISION) return true; return false; }
        
        mat4<T>& operator*=(const mat4<T>& m);
        mat4<T> operator*(const mat4<T>& m) const;

        vec3<T> operator*(const vec3<T>& v) const;
        vec4<T> operator*(const vec4<T>& v) const;

        pnt3<T> operator*(const pnt3<T>& v) const;
        pnt4<T> operator*(const pnt4<T>& v) const;

        T determinant() const;
        T minorDeterminant(int* ci, int level) const;

        mat4<T> reciprocal() const;

        T v[16];
    };

    template <class T>
    mat4<T>& mat4<T>::operator*=(const mat4<T>& m)
    {
        mat4<T> r(*this);
        *this = r * m;
        return *this;
    }

    template <class T>
    mat4<T> mat4<T>::operator*(const mat4<T>& m) const
    {
        mat4<T> r;
        unsigned int i = 16, c, j, k;
        while(i--) {
            c = i & 3;
            k = i & (~3);
            j = 4;
            r[i] = T(0.0);
            while(j--) r[i] += v[k + j] * m[(j << 2) + c];
        }
        return r;
    }

    template <class T>
    vec3<T> mat4<T>::operator*(const vec3<T>& iv) const
    {
        vec3<T> r;
        int i = 3, j, c;
        while(i--) {
            j = 3;
            c = i << 2;
            while(j--) r[i] += v[c + j] * iv[j];
        }
        return r;
    }

    template <class T>
    vec4<T> mat4<T>::operator*(const vec4<T>& iv) const
    {
        vec4<T> r;
        int i = 4, j, c;
        while(i--) {
            j = 4;
            c = i << 2;
            while(j--) r[i] += v[c + j] * iv[j];
        }
        return r;
    }

    template <class T>
    pnt3<T> mat4<T>::operator*(const pnt3<T>& p) const
    {
        pnt3<T> r;
        int i = 3, j, c;
        while(i--) {
            j = 4;
            c = i << 2;
            while(j--) r[i] += v[c + j] * p[j];
        }
        return r;
    }

    template <class T>
    pnt4<T> mat4<T>::operator*(const pnt4<T>& p) const
    {
        pnt4<T> r;
        int i = 4, j, c;
        while(i--) {
            j = 4;
            c = i << 2;
            while(j--) r[i] += v[c + j] * p[j];
        }
        return r;
    }

    template <class T, unsigned int SIZE>
    ostream& operator<<(ostream& os, const vec<T, SIZE>& v)
    {
        unsigned int i = SIZE;
        os << "(";
        while(i--) {
            unsigned int n = SIZE - i - 1;
            if(n) os << ", ";
            os << v[n];
        }
        os << ")";
        return os;
    }

    template <class T>
    T mat4<T>::determinant() const
    {
        int colIndices[] = { 0, 1, 2, 3 };

        return minorDeterminant(colIndices, 4);
    }

    template <class T>
    T mat4<T>::minorDeterminant(int* colIndices, int level) const
    {
        if(level == 2) {
            int i0 = 8 + colIndices[0], i1 = 8 + colIndices[1], i2 = 12 + colIndices[0], i3 = 12 + colIndices[1];
            return v[i0] * v[i3] - v[i2] * v[i1];
        }
        int* minorColIndices = new int[level - 1];
        T det(0.0);
        int o = (4 - level) << 2;
        int i = level;
        while(i--) {
            int j = level - 1;
            while(j--) minorColIndices[j] = colIndices[(j < i) ? j : j + 1];
            det += v[o + colIndices[i]] * minorDeterminant(minorColIndices, level-1) * T((((i & 1) == 0) << 1) - 1);
        }
        delete [] minorColIndices;
        return det;
    }

    template <class T>
    mat4<T> mat4<T>::reciprocal() const
    {
        mat4<T> r;

        // Create augment matrix
        T aug[32];
        int j = 16;
        while(j--) {
            int o = ((j >> 2) << 3) + (j & 3);
            aug[o] = v[j];
            aug[4 + o] = T((j % 5) == 0);
        }
        // Set up array of pointers for efficient row swapping, and simplified indexing
        T* row[] = { aug, aug + 8, aug + 16, aug + 24 };

        // Gauss-Jordan Elimination
        for(j = 0; j < 4; j++) {
            // If the pivot element is zero
            if(row[j][j] == 0.0) 
                // Swap it with a lower row that does not contain zero in the same column
                for(int n = j; n < 4; n++) {
                    if(row[n][j] != 0.0) {
                        T* t = row[n];
                        row[n] = row[j];
                        row[j] = t;
                        break;
                    }
                }

            // If the pivot element is still zero, skip this pivot
            if(row[j][j] != 0.0) {
                // Normalize row so pivot element is 1.0
                T normalizer = 1.0 / row[j][j];
                for(int i = 0; i < 8; i++) 
                    row[j][i] *= normalizer;

                // Use multiple of pivot row to eliminate non-zero elements in the same column in all other rows
                for(int n = 0; n < 4; n++) {
                    T eliminator = row[n][j];
                    if((n != j) && (eliminator != 0.0)) 
                        // Start from j, as elements in previous columns have already been eliminated
                        for(int i = j; i < 8; i++)
                            row[n][i] -= row[j][i] * eliminator;
                }
            }
        }

        // The augment matrix should now be in reduced echelon form, and the right side square sub-matrix 
        // will hold the reciprocal.

        // Return solution
        j = 16;
        while(j--)
            r[j] = row[j >> 2][4 + (j & 3)];

        return r;
    }
    
    template <class T>
    ostream& operator<<(ostream& os, mat4<T>& m)
    {
        os << fixed;
        int i = 16;
        while(i--) {
            int n = 15 - i;
            os << right << setw(20) << setprecision(10) << m[n];
            if(n == 15) os << "\n";
            else {
                if((n % 4) == 3) os << ",\n";
                else os << ",  ";
            }
        }
        os.unsetf(ios::fixed);
        os << left << setw(0) << setprecision(6);
        return os;
    }

    template <class T>
    struct quat {
        quat(T x = T(0.0), T y = T(0.0), T z = T(0.0), T w = T(1.0)) { v[3] = w; v[2] = z; v[1] = y; v[0] = x; }
        // quat(const T* q) { unsigned int i = 4; while(i--) v[i] = q[i]; }
        quat(const T q[4]) { unsigned int i = 4; while(i--) v[i] = q[i]; }
        quat(const quat<T>& q) { unsigned int i = 4; while(i--) v[i] = q[i]; }

        T operator[](unsigned int i) const { return v[i]; }
        T& operator[](unsigned int i) { return v[i]; }

        bool operator==(const quat<T>& q) const { int i = 4; if(ABS(v[i] - q[i]) > FLOAT_PRECISION) return false; return true; }
        bool operator!=(const quat<T>& q) const { int i = 4; if(ABS(v[i] - q[i]) > FLOAT_PRECISION) return true; return false; }
        
        quat<T>& operator+=(const quat& q) { *this = (*this * q); return *this; }
        quat<T> operator+(const quat& q) const {
            quat<T> r(
                v[3] * q[0] + v[0] * q[3] + v[1] * q[2] - v[2] * q[1],
                v[3] * q[1] - v[0] * q[2] + v[1] * q[3] + v[2] * q[0],
                v[3] * q[2] + v[0] * q[1] - v[1] * q[0] + v[2] * q[3],
                v[3] * q[3] - v[0] * q[0] - v[1] * q[1] - v[2] * q[2]
            );
            return r;
        }

        quat<T> operator~() const {
            quat<T> r(T(-1.0) * v[0], T(-1.0) * v[1], T(-1.0) * v[2], v[3]);
            return r;
        }

        quat<T> normalized() const {
            quat<T> r(*this);
            T magRecip = T(1.0) / SQRT(v[0]*v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
            int i = 4;
            while(i--) r[i] *= magRecip;
            return r;
        }

        mat4<T> toMatrix() const {
            mat4<T> r;

            T xy(v[0] * v[1]);
            T xz(v[0] * v[2]);
            T yz(v[1] * v[2]);
            T wx(v[3] * v[0]);
            T wy(v[3] * v[1]);
            T wz(v[3] * v[2]);
            T ww(v[3] * v[3]);

            r[0] = T(2.0) * (ww - T(0.5) + v[0] * v[0]);
            r[1] = T(2.0) * (xy + wz);
            r[2] = T(2.0) * (xz - wy);
            r[3] = T(0.0);

            r[4] = T(2.0) * (xy - wz);
            r[5] = T(2.0) * (ww - T(0.5) + v[1] * v[1]);
            r[6] = T(2.0) * (yz + wx);
            r[7] = T(0.0);

            r[8] = T(2.0) * (xz + wy);
            r[9] = T(2.0) * (yz - wx);
            r[10] = T(2.0) * (ww - T(0.5) + v[2] * v[2]);
            r[11] = T(0.0);

            r[12] = T(0.0);
            r[13] = T(0.0);
            r[14] = T(0.0);
            r[15] = T(1.0); 

            return r;
        }

        vec3<T> toEuler() const {
            T n(v[3] * v[3] - T(0.5));
            vec3<T> r(
                -ATAN2((v[1] * v[2]) - (v[3] * v[0]), n + (v[2] * v[2])),
                ASIN(T(2.0) * ((v[0] * v[2]) + (v[1] * v[3]))),
                -ATAN2((v[0] * v[1]) - (v[2] * v[3]), n + (v[0] * v[0]))
            );
            return r;
            /*
            T n(v[3] * v[3] - T(0.5));
            T sinr_cosp(T(2.0) * (v[0] * v[3] + v[1] * v[2]));
            T cosr_cosp(T(1.0) - T(2.0) * (v[0] * v[0] + v[1] * v[1]));
            T sinp = T(2.0) * (v[1] * v[3] - v[0] * v[2]);
            T asinp;
            if(ABS(sinp) >= T(1.0)) {
                asinp = COPYSIGN(T(M_PI / 2.0), sinp);
            } else {
                asinp = ASIN(sinp);
            }
            T siny_cosp = T(2.0) * (v[2] * v[3] + v[0] * v[1]);
            T cosy_cosp = T(1.0) - T(2.0) * (v[1] * v[1] + v[2] * v[2]);
            vec3<T> r(
                ATAN2(sinr_cosp, cosr_cosp),
                asinp,
                ATAN2(siny_cosp, cosy_cosp)
            );
            */
            return r;
        }

        T v[4];
    };

    template <class S, class U>
    struct rect
    {
        rect(U iw = 0, U ih = 0) : origin(0, 0), size(iw, ih) { }
        rect(S ix, S iy, U iw, U ih) : origin(ix, iy), size(iw, ih) { }
        rect(const pnt2<S>& iOrigin, const vec2<U>& iSize) : origin(iOrigin), size(iSize) { }

        pnt2<S> origin;
        vec2<U> size;
    };
}

#endif
