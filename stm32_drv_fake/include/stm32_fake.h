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

#ifndef __STM32_FAKE_H__
#define __STM32_FAKE_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __IO

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */

#define CAN_ID_STD                  0x00000000U  /*!< Standard Id */
#define CAN_ID_EXT                  0x00000004U  /*!< Extended Id */
#define CAN_RTR_DATA                0x00000000U  /*!< Data frame */
#define CAN_RTR_REMOTE              0x00000002U  /*!< Remote frame */

#define CAN_FILTERMODE_IDMASK       (0x00000000U)  /*!< Identifier mask mode */
#define CAN_FILTERMODE_IDLIST       (0x00000001U)
#define CAN_FILTERSCALE_16BIT       (0x00000000U)  /*!< Two 16-bit filters */
#define CAN_FILTERSCALE_32BIT       (0x00000001U)  /*!< One 32-bit filter  */
#define CAN_FILTER_FIFO0            (0x00000000U)  /*!< Filter FIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO1            (0x00000001U)  /*!< Filter FIFO 1 assignment for filter x */
#define CAN_FILTER_DISABLE          (0x00000000U)  /*!< Disable filter */
#define CAN_FILTER_ENABLE           (0x00000001U)  /*!< Enable filter  */
#define CAN_RX_FIFO0                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x00000001U)  /*!< CAN receive FIFO 1 */

#define HAL_MAX_DELAY      0xFFFFFFFFU

typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;

#define HAL_DMA_STATE_READY 1

typedef struct {
    int32_t State;
} DMA_HandleTypeDef;

typedef struct {
    int32_t dummy;
} UART_HandleTypeDef;

typedef struct {
    int32_t dummy;
} ADC_HandleTypeDef;

typedef struct {
    int32_t dummy;
} CAN_HandleTypeDef;

typedef struct {
    uint32_t StdId;
    uint32_t ExtId;
    uint32_t IDE;
    uint32_t RTR; 
    uint32_t DLC;  
    FunctionalState TransmitGlobalTime;            
} CAN_TxHeaderTypeDef;

typedef struct {
    uint32_t FilterIdHigh;
    uint32_t FilterIdLow;
    uint32_t FilterMaskIdHigh;
    uint32_t FilterMaskIdLow;
    uint32_t FilterFIFOAssignment;
    uint32_t FilterBank; 
    int32_t FilterMode;
    uint32_t FilterScale;
    uint32_t FilterActivation;
    uint32_t SlaveStartFilterBank;
} CAN_FilterTypeDef;

typedef struct {
    uint32_t dummy;
} CAN_RxHeaderTypeDef;

typedef struct {
    int32_t dummy;
} I2C_HandleTypeDef;

typedef struct
{
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t BRR;
    __IO uint32_t LCKR;
} GPIO_TypeDef;

extern int32_t HAL_Tick;
extern uint16_t adcRawValues[16];

HAL_StatusTypeDef 
HAL_UART_Transmit(UART_HandleTypeDef *huart, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout);

uint32_t HAL_GetTick(void);

HAL_StatusTypeDef HAL_CAN_Start(CAN_HandleTypeDef *hcan);

HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, 
                CAN_TxHeaderTypeDef *pHeader,
                uint8_t aData[],
                uint32_t *pTxMailbox);

uint32_t HAL_CAN_GetTxMailboxesFreeLevel(CAN_HandleTypeDef *hcan);

HAL_StatusTypeDef HAL_CAN_ConfigFilter(CAN_HandleTypeDef *hcan, 
                CAN_FilterTypeDef *sFilterConfig);

uint32_t HAL_CAN_GetRxFifoFillLevel(CAN_HandleTypeDef *hcan, uint32_t RxFifo);

HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, 
                uint32_t Timeout);

void HAL_Delay(uint32_t Delay);

HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc,
                uint32_t* pData, 
                uint32_t Length);

HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, 
                uint32_t RxFifo, 
                CAN_RxHeaderTypeDef *pHeader, 
                uint8_t aData[]);

HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, 
                uint16_t DevAddress, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, 
                uint16_t DevAddress, 
                uint8_t *pData, 
                uint16_t Size, 
                uint32_t Timeout);


GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
// GLOBALS
extern GPIO_TypeDef _GPIOA;
extern GPIO_TypeDef _GPIOB;
extern GPIO_TypeDef _GPIOC;
extern GPIO_TypeDef _GPIOD;

#define GPIOA       ((GPIO_TypeDef*)&_GPIOA)
#define GPIOB       ((GPIO_TypeDef*)&_GPIOB)
#define GPIOC       ((GPIO_TypeDef*)&_GPIOC)
#define GPIOD       ((GPIO_TypeDef*)&_GPIOD)

// GLOBALS defined by user
extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_adc1;

extern CAN_HandleTypeDef hcan;

extern UART_HandleTypeDef huart1;

#ifdef __cplusplus
}
#endif

#endif // __STM32_FAKE_H__