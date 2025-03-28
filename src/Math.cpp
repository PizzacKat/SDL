#include "SDL/Math.hpp"

namespace SDL {
    float Cos(const Angle &angle) {
        return SDL_cosf(angle.AsRadians());
    }

    float Sin(const Angle &angle) {
        return SDL_sinf(angle.AsRadians());
    }

    float Tan(const Angle &angle) {
        return SDL_tanf(angle.AsRadians());
    }

    Angle Acos(const float x) {
        return FromRadians(SDL_acosf(x));
    }

    Angle Asin(const float x) {
        return FromRadians(SDL_asinf(x));
    }

    Angle Atan(const float x) {
        return FromRadians(SDL_atanf(x));
    }

    Angle Atan2(const FVector2 &vec2) {
        return FromRadians(SDL_atan2(vec2.y, vec2.x));
    }

    float Sqrt(const float x) {
        return SDL_sqrtf(x);
    }

    int Abs(const int x) {
        return SDL_abs(x);
    }

    double Abs(const double x) {
        return SDL_fabs(x);
    }

    float Abs(const float x) {
        return SDL_fabsf(x);
    }

    double Mod(const double x, const double y) {
        return SDL_fmod(x, y);
    }

    float Mod(const float x, const float y) {
        return SDL_fmodf(x, y);
    }

    double Ceil(const double x) {
        return SDL_ceil(x);
    }

    float Ceil(const float x) {
        return SDL_ceilf(x);
    }

    double Floor(const double x) {
        return SDL_floor(x);
    }

    float Floor(const float x) {
        return SDL_floorf(x);
    }

    double Exp(const double x) {
        return SDL_exp(x);
    }

    float Exp(const float x) {
        return SDL_expf(x);
    }

    double Log(const double x) {
        return SDL_log(x);
    }

    float Log(const float x) {
        return SDL_logf(x);
    }

    double Log10(const double x) {
        return SDL_log10(x);
    }

    float Log10(const float x) {
        return SDL_log10f(x);
    }

    double Round(const double x) {
        return SDL_round(x);
    }

    float Round(const float x) {
        return SDL_roundf(x);
    }

    long LongRound(const double x) {
        return SDL_lround(x);
    }

    long LongRound(const float x) {
        return SDL_lroundf(x);
    }
}
