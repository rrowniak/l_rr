/*
 * Copyright (c) 2019 Rafal Rowniak rrowniak.com
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

#include "lrr_math.h"

// https://en.wikipedia.org/wiki/Linear_interpolation
inline float lrr_math_lin_interpolation(float x0, float y0, float x1, 
                                        float y1, float x) {
    return (y0 * (x1 - x) + y1 * (x - x0)) / (x1 - x0);
}

static int _find_points(const float observed[][2], const int observed_size, 
                float *x0, float *y0, float *x1, float *y1, float x) {
    // linear algorithm, in case of performance problems rewrite to binary search
    for (int i = 0; i < observed_size - 1; i++) {
        if (x >= observed[i][0] && x < observed[i + 1][0]) {
            *x0 = observed[i][0]; *y0 = observed[i][1];
            *x1 = observed[i + 1][0]; *y1 = observed[i + 1][1];
            return 1;
        }
    }

    return 0;
}

float lrr_get_corrected(const float observed[][2], int observed_size, float input) {
    float x0, y0, x1, y1;
    if (_find_points(observed, observed_size, &x0, &y0, &x1, &y1, input)) {
        return lrr_math_lin_interpolation(x0, y0, x1, y1, input);
    }

    // linear extrapolation is not supported yet
    return input;
}
