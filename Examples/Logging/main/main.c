/**
 * @file main.c
 * @author Omegaki113r
 * @date Saturday, 29th June 2024 3:24:38 am
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: Logging
 * File Name: main.c
 * File Created: Saturday, 29th June 2024 3:24:38 am
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Monday, 1st July 2024 1:01:09 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_log.h>
#include <esp_spiffs.h>

#include "OmegaFileSystemController.h"
#include "OmegaLoggingSystemController.h"

void app_main(void)
{
    esp_vfs_spiffs_conf_t spiffs_config = {
        .base_path = "/storage",
        .max_files = 5,
        // .partition_label = "storage",
        .format_if_mount_failed = false,
    };
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&spiffs_config));
    {
        FileHandle handle = OmegaFileSystemController_open_file("/storage/log.txt", eREADING);
        const size_t sz = OmegaFileSystemController_get_file_size(handle);
        char *buf = malloc(sz + 1);
        if (buf == NULL)
            return;
        size_t read_size = 0;
        while ((read_size = OmegaFileSystemController_read_file(handle, eREAD_LINE, (uint8_t *)buf, sz)) > 0)
        {
            OMEGA_PLOGI("%s", buf);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        OmegaFileSystemController_close_file(handle);
        free(buf);
    }
    uint64_t i = 0;
    for (;;)
    {
        PROFILE_START(__func__);
        OMEGA_PLOGI("%llu", i++);
        OMEGA_EVENTLOGI("hello world");
        vTaskDelay(pdMS_TO_TICKS(100));
        PROFILE_END(__func__);
    }
}
