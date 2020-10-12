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

#ifndef __LRR_MATH_H__
#define __LRR_MATH_H__
#ifdef __cplusplus
extern "C" {
#endif

float lrr_math_lin_interpolation(float x0, float y0, float x1, 
                                        float y1, float x);
// error correction routines

// EXAMPLE:
// {observed (what device measures), expected (what multimeter shows)}
// ascending order, at least two rows
// static const float observed[][2] = {
//     {50, 53.63},
//     {54.75, 58.38},
//     {78.9, 83.8},
//     {85.1, 90},
// };

// static const int observed_size = sizeof(observed) / sizeof(observed[0]);

float lrr_get_corrected(const float observed[][2], int observed_size, float input);

#ifdef __cplusplus
}
#endif
#endif // __LRR_MATH_H__
