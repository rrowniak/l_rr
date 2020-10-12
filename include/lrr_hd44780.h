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

#ifndef __hd44780_h
#define __hd44780_h

#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _LCD_DEFAULT_CFG_

#define LCD_CTRL_PORT LCD_E_GPIO_Port
#define LCD_RS LCD_RS_Pin
#define LCD_RW LCD_RW_Pin
#define LCD_EN LCD_E_Pin

#define LCD_DATA_PORT LCD_D4_GPIO_Port
#define LCD_D4 LCD_D4_Pin
#define LCD_D5 LCD_D5_Pin
#define LCD_D6 LCD_D6_Pin
#define LCD_D7 LCD_D7_Pin

#define LCD_COL_COUNT 16
#define LCD_ROW_COUNT 2

#else
#include "lrr_hd44780.def"
#endif

void lcd_init(void);

void lcd_command(uint8_t command);
void lcd_write(uint8_t value);

void lcd_on(void);
void lcd_off(void);

void lcd_clear(void);
void lcd_return_home(void);

void lcd_enable_blinking(void);
void lcd_disable_blinking(void);

void lcd_enable_cursor(void);
void lcd_disable_cursor(void);

void lcd_scroll_left(void);
void lcd_scroll_right(void);

void lcd_set_left_to_right(void);
void lcd_set_right_to_left(void);

void lcd_enable_autoscroll(void);
void lcd_disable_autoscroll(void);

void lcd_create_char(uint8_t location, uint8_t *charmap);

void lcd_set_cursor(uint8_t col, uint8_t row);

void lcd_puts(const char *string);
void lcd_println(const char *string, uint8_t line);
void lcd_printf(const char *format, ...);
void lcd_printfln(const char *format, ...);

#ifdef __cplusplus
}
#endif


#endif // __hd44780_h
