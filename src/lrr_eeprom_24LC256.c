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

#include <lrr_eeprom_24LC256.h>
#include <lrr_usart.h>
#include <memory.h>

#define IC2_TIMEOUT 1000
#define DEVICE_ADDR 0xA0

I2C_HandleTypeDef* i2c_dev = NULL;

void eeprom_24lc256_init(I2C_HandleTypeDef* dev)
{
    i2c_dev = dev;
}

static HAL_StatusTypeDef _write8(uint16_t eeprom_addr, 
    const uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef ret;
    static uint8_t data_tmp[10];

    data_tmp[0] = (uint8_t) ((eeprom_addr & 0xFF00) >> 8);
    data_tmp[1] = (uint8_t) (eeprom_addr & 0xFF);

    memcpy(data_tmp + 2, data, size);

    ret = HAL_I2C_Master_Transmit(i2c_dev, DEVICE_ADDR, data_tmp, size + 2, HAL_MAX_DELAY);
    if (ret != HAL_OK) {
        return ret;
    }

    // wait until the EEPROM effectively stores data in memory
    while (HAL_I2C_Master_Transmit(i2c_dev, DEVICE_ADDR, 0, 0, HAL_MAX_DELAY) != HAL_OK);

    return HAL_OK;
}

HAL_StatusTypeDef eeprom_24lc256_write(uint16_t eeprom_addr, 
    const uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef ret;
    uint16_t i = 0;

    for (; i < size; i += 8) {
        ret = _write8(eeprom_addr + i, data + i, (size - i) > 8? 8 : size - i);
        if (ret != HAL_OK) {
            return ret;
        }
    }

    return HAL_OK;
}

HAL_StatusTypeDef eeprom_24lc256_read(uint16_t eeprom_addr, 
    uint8_t *data, uint16_t size)
{
    HAL_StatusTypeDef ret;
    uint8_t addr[2];

    addr[0] = (uint8_t) ((eeprom_addr & 0xFF00) >> 8);
    addr[1] = (uint8_t) (eeprom_addr & 0xFF);

    // send the memory location address
    ret = HAL_I2C_Master_Transmit(i2c_dev, DEVICE_ADDR, addr, 2, HAL_MAX_DELAY);
    if (ret != HAL_OK) {
        return ret;
    }

    // read data
    ret = HAL_I2C_Master_Receive(i2c_dev, DEVICE_ADDR, data, size, HAL_MAX_DELAY);

    return ret;
}
