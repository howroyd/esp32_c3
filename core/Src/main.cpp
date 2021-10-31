#include "main.h"

SUPPRESS_WARN_BEGIN
#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG
#include "esp_log.h"
#define LOG_TAG "MAIN"
SUPPRESS_WARN_END

#include <iostream>
static void print_chip_info(void);

static Main main_class{};

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
extern "C" void app_main(void)
{
    ESP_LOGD(LOG_TAG, "Creating default event loop");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGD(LOG_TAG, "Initialising NVS");
    ESP_ERROR_CHECK(nvs_flash_init());

    ESP_LOGI(LOG_TAG, "Initialising main task: %s", esp_err_to_name(main_class.init()));
}
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
bool Main::setup(Main &main)
{
    esp_err_t status{ESP_OK};

    status |= start_all_tasks();

    return status == ESP_OK;
}

// --------------------------------------------------------------------------------
void Main::loop(Main &main)
{
    // Main user run code
    print_chip_info();
    vTaskDelay(pdSECOND * 5);
}

// --------------------------------------------------------------------------------
// Function to start tasks by notification
[[nodiscard]] esp_err_t Main::start_all_tasks(void)
{
    esp_err_t ret_status{ESP_OK};

    ESP_LOGI(tag, "%s", __func__);

    return ret_status;
}

// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------

[[maybe_unused]] static void print_chip_info(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    std::cout << "This is " << CONFIG_IDF_TARGET << " chip with " << (int)chip_info.cores << " CPU core(s), WiFi" << ((chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "") << ((chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "") << ", silicon revision " << (int)chip_info.revision << ", " << spi_flash_get_chip_size() / (1024 * 1024) << "MB " << ((chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external") << " flash\n";

    std::cout << "Minimum free heap size: " << esp_get_minimum_free_heap_size() << " bytes\n";
}