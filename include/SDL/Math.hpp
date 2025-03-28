#ifndef MATH_HPP
#define MATH_HPP

#include "Angle.hpp"
#include "Vector.hpp"

namespace SDL {
    float Cos(const Angle &angle);
    float Sin(const Angle &angle);
    float Tan(const Angle &angle);

    Angle Acos(float x);
    Angle Asin(float x);
    Angle Atan(float x);
    Angle Atan2(const FVector2 &vec2);

    float Sqrt(float x);

    int Abs(int x);
    double Abs(double x);
    float Abs(float x);

    double Mod(double x, double y);
    float Mod(float x, float y);

    double Ceil(double x);
    float Ceil(float x);

    double Floor(double x);
    float Floor(float x);

    double Exp(double x);
    float Exp(float x);

    double Log(double x);
    float Log(float x);

    double Log10(double x);
    float Log10(float x);

    double Round(double x);
    float Round(float x);
    long LongRound(double x);
    long LongRound(float x);
}

#endif //MATH_HPP
