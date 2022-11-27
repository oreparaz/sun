// sun: compute sunrise/sunset times
//
// https://github.com/oreparaz/sun
//
// (c) 2022 Oscar Reparaz <firstname.lastname@esat.kuleuven.be>

#ifndef SUN_H
#define SUN_H

#include <stddef.h>
#include <stdint.h>

typedef uint64_t fti_sample_t;

typedef struct sun_ctx_t {
    double in_latitude;
    double in_longitude;
    uint32_t in_yday; // number of days since Jan 1, in the range of 0 to 365
    uint32_t in_hour; // number of hours past midnight (range 0 to 23)
    double out_sunrise_mins; // minutes after midnight (UTC)
    double out_sunset_mins;
} sun_ctx_t;

typedef enum {
    SUN_SUCCESS = 0,
    SUN_ERROR,
} sun_ret_t;

#ifdef __cplusplus
extern "C" {
#endif

sun_ret_t sun_compute(sun_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

#endif //SUN_H
