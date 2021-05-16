/**
 * @file aht10.h
 * @author Sergey Tkachenko (sergey.iray@yandex.ru)
 * @brief Platform-agnostic AHT10 library for embedded systems
 * @version 0.1
 * @date 2021-05-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief AHT10 error code definitions
 * 
 */
typedef enum {
    AHT10_OK = 0, /**< No error*/
    AHT10_INIT, /**< Initializing error*/
    AHT10_ERR_LEN
} aht10_err;

/**
 * @brief AHT10 I2C driver 
 * 
 */
typedef struct
{
    void (*write)(uint8_t* data, uint32_t len); /**< I2C write function prototype*/
    void (*read)(uint8_t* data, uint32_t len); /**< I2C read function prototype*/
} aht10_driver_t;

/**
 * @brief Initializes AHT10
 * 
 * @param driver pointer to aht10_driver_t driver structure
 * @return aht10_err Error code
 */
aht10_err aht10_init(aht10_driver_t* driver);

#ifdef __cplusplus
}
#endif