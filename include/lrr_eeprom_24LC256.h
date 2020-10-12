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

#ifndef __EEPROM_24LC256_H__
#define __EEPROM_24LC256_H__

#include "stm32f1xx_hal.h"

void eeprom_24lc256_init(I2C_HandleTypeDef* dev);
HAL_StatusTypeDef eeprom_24lc256_write(uint16_t eeprom_addr, 
    const uint8_t *data, uint16_t size);
HAL_StatusTypeDef eeprom_24lc256_read(uint16_t eeprom_addr, 
    uint8_t *data, uint16_t size);

#endif //__EEPROM_24LC256_H__