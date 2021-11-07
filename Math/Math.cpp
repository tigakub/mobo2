#include "Math.hpp"

namespace mobo
{
    float COPYSIGN(float s, float t) { return copysignf(s, t); }
    double COPYSIGN(double s, double t) { return copysign(s, t); }
    float SIN(float s) { return sinf(s); }
    double SIN(double s) { return sin(s); }
    float COS(float s) { return cosf(s); }
    double COS(double s) { return cos(s); }
    float TAN(float s) { return tanf(s); }
    double TAN(double s) { return tan(s); }
    float ASIN(float s) { return sinf(s); }
    double ASIN(double s) { return sin(s); }
    float ACOS(float s) { return cosf(s); }
    double ACOS(double s) { return cos(s); }
    float ATAN2(float y, float x) { return atan2f(y, x); }
    double ATAN2(double y, double x) { return atan2(y, x); }
    float SQRT(float s) { return sqrtf(s); }
    double SQRT(double s) { return sqrt(s); }
    float ABS(float s) { return fabs(s); }
    double ABS(double s) { return abs(s); }
}