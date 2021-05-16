#include "aht10.h"

static const uint8_t AHT10_CMD_SIZE = 1;
static const uint8_t AHT10_DATA_SIZE = 6;
static const uint8_t AHT10_CMD_MEASURE_SIZE = 3;
static const uint8_t AHT10_CMD_MEASURE_B1 = 0x33;
static const uint8_t AHT10_CMD_MEASURE_B2 = 0x00;

static aht10_driver_t* drv = NULL;
static aht10_status_t status;
static aht10_data_t data;

aht10_err aht10_init(aht10_driver_t* driver)
{
    aht10_err err = AHT10_INIT;

    status.status_byte = 0x00;

    if (driver) {
        drv = driver;

        err = AHT10_OK;
    }
    return err;
}

void aht10_command_send(aht10_cmd_e cmd)
{
    uint8_t command[3] = { 0, 0, 0 };
    uint32_t len = 0;

    command[0] = (uint8_t)cmd;

    switch (cmd) {
    case AHT10_CMD_INIT:
        len = AHT10_CMD_SIZE;
        break;
    case AHT10_CMD_MEASURE:
        len = AHT10_CMD_MEASURE_SIZE;
        command[1] = AHT10_CMD_MEASURE_B1;
        command[2] = AHT10_CMD_MEASURE_B2;
        break;
    case AHT10_CMD_RESET:
        len = AHT10_CMD_SIZE;
        break;
    default:
        len = 0;
        break;
    }

    if (len && drv) {
        if (drv->write) {
            drv->write(command, len);
        }
    }
}

aht10_data_t aht10_data_get()
{
    /* Received data: STATUS[1]:HIMIDITY[2.5]:TEMPERATURE[2.5] */
    uint8_t data_raw[AHT10_DATA_SIZE];
    if (drv) {
        if (drv->read) {
            drv->read(data_raw, AHT10_DATA_SIZE);
        }

        status.status_byte = data_raw[0];

        data.temperature = (((uint32_t)data_raw[3] & 15) << 16) | ((uint32_t)data_raw[4] << 8) | data_raw[5];
        data.humidity = ((uint32_t)data_raw[1] << 12) | ((uint32_t)data_raw[2] << 4) | (data_raw[3] >> 4);
    }
    return data;
}

aht10_status_t* aht10_status_get()
{
    return &status;
}
