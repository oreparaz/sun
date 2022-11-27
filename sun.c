// sun: compute sunrise/sunset times
//
// https://github.com/oreparaz/sun
//
// (c) 2022 Oscar Reparaz <firstname.lastname@esat.kuleuven.be>

#include "sun.h"
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#define deg2rad(deg) ((deg) * (M_PI / 180.0))
#define rad2deg(rad) ((rad) * (180.0 / M_PI))

// sun_compute follows:
//
//    General Solar Position Calculations
//    NOAA Global Monitoring Division
//    https://gml.noaa.gov/grad/solcalc/solareqns.PDF
//
// TODO: handle leap years
// TODO: handle invalid arguments (invalid lon/lat)
sun_ret_t sun_compute(sun_ctx_t *ctx)
{

    // fractional year [radians]
    double gamma = ctx->in_yday + ((ctx->in_hour - 12.0) / 24.0);
    gamma = gamma * 2.0 * M_PI / 365.0;

    double cosGamma = cos(gamma);
    double cos2Gamma = cos(2 * gamma);
    double cos3Gamma = cos(3 * gamma);

    double sinGamma = sin(gamma);
    double sin2Gamma = sin(2 * gamma);
    double sin3Gamma = sin(3 * gamma);

    // equation of time [minutes]
    double eqtime = 0.000075 +
                    0.001868 * cosGamma +
                    -0.032077 * sinGamma +
                    -0.014615 * cos2Gamma +
                    -0.040849 * sin2Gamma;
    eqtime = eqtime * 229.18;

    // solar declination angle [radians]
    double decl = -0.399912 * cosGamma + 0.070257 * sinGamma;
    decl = decl + -0.006758 * cos2Gamma + 0.000907 * sin2Gamma;
    decl = decl + -0.002697 * cos3Gamma + 0.00148 * sin3Gamma;
    decl = decl + 0.006918;

    // hour angle [radians]
    double ha_sunrise = acos(((cos(deg2rad(90.833))) / (cos(deg2rad(ctx->in_latitude)) * cos(decl))) - tan(deg2rad(ctx->in_latitude)) * tan(decl));
    double ha_sunset = -ha_sunrise;

    // sunrise [minutes]
    double sunRise = 720 - 4 * (ctx->in_longitude + rad2deg(ha_sunrise)) - eqtime;
    double sunSet = 720 - 4 * (ctx->in_longitude + rad2deg(ha_sunset)) - eqtime;

    ctx->out_sunrise_mins = sunRise;
    ctx->out_sunset_mins = sunSet;

    return SUN_SUCCESS;
}
