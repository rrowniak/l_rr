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

#include <stm32_fake.h>
#include <stm32_puppet.hpp>

#include <iostream>
#include <cstring>
#include <cassert>

std::vector<CanMessage> canBusBuffer;

class EepromI2C_24LC256
{
private:
    static constexpr size_t MaxAddr = 256 * 1024;
    uint8_t memory[MaxAddr];
    size_t addr_reg = MaxAddr;
public:
    HAL_StatusTypeDef MasterTransmit(const uint8_t* buff, size_t size)
    {
        if (buff == nullptr || size == 0) {
            return HAL_OK;
        }

        // first two bytes are addresses
        uint16_t addr = buff[0] << 8;
        addr |= buff[1];

        assert(addr < MaxAddr);
        assert(addr + size - 2 < MaxAddr);

        if (size == 2) {
            addr_reg = addr;
            return HAL_OK;
        }

        memcpy(&memory[addr], buff + 2, size - 2);

        return HAL_OK;
    }

    HAL_StatusTypeDef MasterReceive(uint8_t* buff, size_t size)
    {
        assert(buff != nullptr);
        assert(size > 2);

        assert(addr_reg < MaxAddr);

        memcpy(buff, &memory[addr_reg], size - 2);

        addr_reg = MaxAddr;

        return HAL_OK;
    }
};

EepromI2C_24LC256 eeprom;

extern "C" {

GPIO_TypeDef _GPIOA;
GPIO_TypeDef _GPIOB;
GPIO_TypeDef _GPIOC;
GPIO_TypeDef _GPIOD;

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_adc1;

CAN_HandleTypeDef hcan;

UART_HandleTypeDef huart1;


int32_t HAL_Tick = 0;
uint16_t adcRawValues[16];

HAL_StatusTypeDef 
HAL_UART_Transmit(UART_HandleTypeDef *huart, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout)
{
    for (int i = 0; i < Size; ++i) {
        std::cout << (char)pData[i];
    }
    return HAL_OK;
}

uint32_t HAL_GetTick(void)
{
    return HAL_Tick;
}

HAL_StatusTypeDef HAL_CAN_Start(CAN_HandleTypeDef *hcan)
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, 
                CAN_TxHeaderTypeDef *pHeader,
                uint8_t aData[],
                uint32_t *pTxMailbox)
{
    canBusBuffer.emplace_back();
    memcpy(&canBusBuffer.back().header, pHeader, sizeof(CAN_TxHeaderTypeDef));
    memcpy(canBusBuffer.back().data, aData, 8);
    return HAL_OK;
}

uint32_t HAL_CAN_GetTxMailboxesFreeLevel(CAN_HandleTypeDef *hcan)
{
    return 3;
}

HAL_StatusTypeDef HAL_CAN_ConfigFilter(CAN_HandleTypeDef *hcan, CAN_FilterTypeDef *sFilterConfig)
{
    return HAL_OK;
}

uint32_t HAL_CAN_GetRxFifoFillLevel(CAN_HandleTypeDef *hcan, uint32_t RxFifo)
{
    return canBusBuffer.size();
}

HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, 
                uint32_t RxFifo,
                CAN_RxHeaderTypeDef *pHeader,
                uint8_t aData[])
{
    if (canBusBuffer.empty()) {
        return HAL_ERROR;
    }

    memcpy(aData, canBusBuffer.back().data, 8);
    canBusBuffer.pop_back();

    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc)
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc)
{
    return HAL_OK;
}

uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)
{
    return adcRawValues[0];
}

HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, 
                uint32_t Timeout)
{
    return HAL_OK;
}

void HAL_Delay(uint32_t Delay)
{

}

HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc)
{
    return HAL_OK;
}

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc,
                uint32_t* pData, 
                uint32_t Length)
{
    memcpy(pData, adcRawValues, Length * sizeof(uint16_t));
    return HAL_OK;
}


HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, 
                uint16_t DevAddress, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout)
{
    // TODO: device selector needed, now only eeprom supported
    return eeprom.MasterTransmit(pData, Size);
}

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, 
                uint16_t DevAddress, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout)
{
    // TODO: device selector needed, now only eeprom supported
    return eeprom.MasterReceive(pData, Size);
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return GPIO_PIN_SET;
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{

}
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

}

}

std::vector<CanMessage>& GetCanBusBuffer()
{
    return canBusBuffer;
}

void InsertCanMessage(const CanMessage& msg)
{
    canBusBuffer.push_back(msg);
}