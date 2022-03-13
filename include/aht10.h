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

typedef enum {
    AHT10_CMD_INIT = 0xE1,
    AHT10_CMD_MEASURE = 0xAC,
    AHT10_CMD_RESET = 0xBA,
} aht10_cmd_e;

/**
 * @brief AHT10 I2C driver
 *
 */
typedef struct
{
    void (*write)(uint8_t* data, uint32_t len); /**< I2C write function prototype*/
    void (*read)(uint8_t* data, uint32_t len); /**< I2C read function prototype*/
} aht10_driver_t;

typedef union {
    struct
    {
        uint8_t reserved_02 : 3;
        uint8_t calibrated : 1;
        uint8_t reserved_4 : 1;
        uint8_t mode : 2;
        uint8_t busy : 1;
    } bits;
    uint8_t status_byte;
} aht10_status_t;

/**
 * @brief AHT10 measurement data
 *
 */
typedef struct {
    uint32_t temperature;
    uint32_t humidity;
} aht10_data_t;

/**
 * @brief Initializes AHT10
 *
 * @param driver pointer to aht10_driver_t driver structure
 * @return aht10_err Error code
 */
aht10_err aht10_init(aht10_driver_t* driver);

void aht10_command_send(aht10_cmd_e cmd);
aht10_data_t aht10_data_get();
aht10_status_t* aht10_status_get();

#ifdef __cplusplus
}
#endif