# sun

`sun` is C library to compute sunrise/sunset times targeting embedded use. 

## Algorithm

`sun` currently uses the method described in:

> General Solar Position Calculations
>
> NOAA Global Monitoring Division

This doc is available at https://gml.noaa.gov/grad/solcalc/solareqns.PDF

## Details

`sun` relies on `math.h` for computing trigonometric functions.
