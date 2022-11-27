#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "byte_vec.h"
#include "../sun.h"

static const double MAX_ALLOWED_ERROR_MINUTES = 4.0;

typedef struct sun_testcase_t {
    double in_latitude;
    double in_longitude;
    uint32_t in_yday;
    uint32_t in_hour;
    double expected_sunrise_mins;
    double expected_sunset_mins;
} sun_testcase_t;

TEST_CASE("test sun") {
    sun_testcase_t testcases[] = {
        #include "vectors.inc"
    };

    int number_tests =  sizeof(testcases) / sizeof(testcases[0]);
    REQUIRE(number_tests > 10);

    for (int i=0; i<number_tests; i++) {
        sun_ctx_t ctx = {
            .in_latitude  = testcases[i].in_latitude,
            .in_longitude = testcases[i].in_longitude,
            .in_yday = testcases[i].in_yday,
            .in_hour = testcases[i].in_hour,
        };
        REQUIRE(sun_compute(&ctx) == SUN_SUCCESS);
        REQUIRE( abs(ctx.out_sunrise_mins - testcases[i].expected_sunrise_mins) < MAX_ALLOWED_ERROR_MINUTES);
        REQUIRE( abs(ctx.out_sunset_mins - testcases[i].expected_sunset_mins) < MAX_ALLOWED_ERROR_MINUTES);
    }
}

TEST_CASE("example usage") {
    // worked out example: let's compute sunrise/sunset time in Malaga - Spain on 2016-03-23.
    // March, 23rd is day of the year number 81
    // UTC offset: +1.0 hours
    // Lat/Lon: 36.7201600, -4.4203400
    
    sun_ctx_t ctx = {
        .in_latitude  = 36.7201600,
        .in_longitude = -4.4203400,
        .in_yday = 81,
        .in_hour = 0,
    };

    sun_ret_t ret = sun_compute(&ctx);
    REQUIRE(ret == SUN_SUCCESS);

    // the expected UTC time for sunrise is 07:19
    // => local sunrise happens at 08:19

    double const utc_offset = 1.0 * 60;
    double sunrise_mins_local = ctx.out_sunrise_mins + utc_offset;

    uint32_t sunrise_hour = (uint32_t)(sunrise_mins_local/60); 
    uint32_t sunrise_min  = ((uint32_t)sunrise_mins_local%60);
    REQUIRE(sunrise_hour == 7);
    REQUIRE(sunrise_min  == 19);
}

