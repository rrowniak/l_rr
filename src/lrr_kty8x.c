/*
 * Copyright (c) 2020 Rafal Rowniak rrowniak.com
 * 
 * The author hereby grant you a non-exclusive, non-transferable,
 * free of charge right to copy, modify, merge, publish and distribute,
 * the Software for the sole purpose of performing non-commercial
 * scientific research, non-commercial education, or non-commercial 
 * artistic projects.
 * 
 * Any other use, in particular any use for commercial purposes,
 * is prohibited. This includes, without limitation, incorporation
 * in a commercial product, use in a commercial service, or production
 * of other artefacts for commercial purposes.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include "lrr_kty8x.h"
#include "lrr_math.h"

static const float kty83_122_map[][2] =
{
    {505,           -55},
    {530,           -50},
    {583,           -40},
    {639,           -30},
    {698,           -20},
    {762,           -10},
    {828,           0},
    {898,           10},
    {972,           20},
    {1010,          25},
    {1049,          30},
    {1130,          40},
    {1214,          50},
    {1301,          60},
    {1392,          70},
    {1487,          80},
    {1585,          90},
    {1687,          100},
    {1792,          110},
    {1900,          120},
    {1956,          125},
    {2012,          130},
    {2128,          140},
    {2247,          150},
    {2370,          160},
    {2496,          170},
    {2560,          175},
    // dummy value (terminator)
    {10999,         299}
};

static const float kty81_120_map[][2] = 
{
//   OHM          Celcius
    {490,         -55},
    {515,         -50},
    {567,         -40},
    {624,         -30},
    {684,         -20},
    {747,         -10},
    {815,         0},
    {886,         10},
    {961,         20},
    {1000,        25},
    {1040,        30},
    {1122,        40},
    {1209,        50},
    {1299,        60},
    {1392,        70},
    {1490,        80},
    {1591,        90},
    {1696,        100},
    {1805,        110},
    {1915,        120},
    {1970,        125},
    {2023,        130},
    {2124,        140},
    {2211,        150},
    // dummy value (terminator)
    {10999,         299}
};

static const float ntc_map[][2] = 
{
//   OHM              Celcius
    {0,                 999.0},
    {310.0,             150.0},
    {597.0,             120.0},
    {1234.0,            80.56},
    {1718.0,            70.56},
    {2438.0,            60.56},
    {3525.0,            50.56},
    {5207.0,            40.56},
    {7866.0,            30.56},
    {10000.0,            25.0},
    {12182.0,           20.56},
    {19376.0,           10.56},
    {31732.0,           0.56},
    {57017.0,           -10.56},
    {100218.0,          -20.56},
    // dummy value (terminator)
    {200999.0,          -40.99}
};

float kty83_122_get_temp(float kt_resistance)
{
    return lrr_get_corrected(kty83_122_map, 
        sizeof(kty83_122_map) / sizeof(kty83_122_map[0]),
        kt_resistance);
}

float kty81_120_get_temp(float kt_resistance)
{
    return lrr_get_corrected(kty81_120_map, 
        sizeof(kty81_120_map) / sizeof(kty81_120_map[0]),
        kt_resistance);
}

float ntc_get_temp(float ntc_resistance)
{
    return lrr_get_corrected(ntc_map, 
        sizeof(ntc_map) / sizeof(ntc_map[0]),
        ntc_resistance);
}