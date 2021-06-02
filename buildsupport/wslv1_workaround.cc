/*
 * Declare the external symbol on the main of each thread/process running in WSLv1
 * to configure floating point correctly
 *
 * #ifdef __WSLv1__
 *   extern void wslv1_workaround();
 * #endif
 * int main (int argc, char *argv[])
 * {
 *   #ifdef __WSLv1__
 *      wslv1_workaround()
 *   #endif
 *   ...
 */

#include <fpu_control.h>
#include <xmmintrin.h>
#include <fenv.h>

void wslv1_workaround()
{
    // More info in https://github.com/microsoft/WSL/issues/830
    // workaround for issues in int64x64 due to long-double being 64-bit instead of 80-bit
    unsigned short cw = 0x37f;
    _FPU_SETCW(cw);

    // workaround for basic-data-calculators (and future tests) not being rounded correctly when using SIMD
    fesetround(FE_TOWARDZERO);
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
}