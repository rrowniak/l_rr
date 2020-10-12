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

#include <lrr_hd44780.h>
#include <hd44780_puppet.hpp>

#include <cstring>
#include <cassert>
#include <stdarg.h>

const char* hd44780_get_frame()
{
    return "----------------";
}

std::string line1;
std::string line2;

int curr_cur_row = 0;
int curr_cur_col = 0;

const std::string& hd44780_get_line1()
{
    return line1;
}

const std::string& hd44780_get_line2()
{
    return line2;
}

extern "C" {

void lcd_init(void)
{
    line1 = "";
    line2 = "";
}

void lcd_command(uint8_t command)
{ }
void lcd_write(uint8_t value)
{ }

void lcd_on(void)
{ }
void lcd_off(void)
{ }

void lcd_clear(void)
{
    line1 = "";
    line2 = "";
}
void lcd_return_home(void)
{ }

void lcd_enable_blinking(void)
{ }
void lcd_disable_blinking(void)
{ }

void lcd_enable_cursor(void)
{ }
void lcd_disable_cursor(void)
{ }

void lcd_scroll_left(void)
{ }
void lcd_scroll_right(void)
{ }

void lcd_set_left_to_right(void)
{ }
void lcd_set_right_to_left(void)
{ }

void lcd_enable_autoscroll(void)
{ }
void lcd_disable_autoscroll(void)
{ }

void lcd_create_char(uint8_t location, uint8_t *charmap)
{ }

void lcd_set_cursor(uint8_t col, uint8_t row)
{
    assert(row < 2);
    assert(col < 16);

    curr_cur_row = row;
    curr_cur_col = col;    
}

void lcd_puts(const char *string)
{
    assert(strlen(string) + curr_cur_col <= 16);
    std::string l;
    l.insert(0, curr_cur_col, ' ');
    l += string;
    
    if (curr_cur_row) {
        line2 = l;
    } else {
        line1 = l;
    }
}

void lcd_println(const char *string, uint8_t line)
{
    lcd_set_cursor(0, line);
    lcd_puts(string);
}

void lcd_printf(const char *format, ...)
{
    char buff[256];

    va_list arglist;
    va_start(arglist, format);
    vsnprintf(buff, 256, format, arglist);
    va_end(arglist);

    lcd_puts(buff);
}

void lcd_printfln(const char *format, ...)
{
    char buff[256];

    va_list arglist;
    va_start(arglist, format);
    vsnprintf(buff, 256, format, arglist);
    va_end(arglist);

    lcd_puts(buff);
}

}