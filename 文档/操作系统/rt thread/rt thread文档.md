### 在已有bsp上更换不同型号mcu的bsp

1. 找到需要更换的bsp的`.config`文件看他使能了哪些`HAL & SDK Drivers`文件，以at32f407举例：

   ```
   CONFIG_PKG_USING_AT32F403A_407_HAL_DRIVER=y
   CONFIG_PKG_AT32F403A_407_HAL_DRIVER_PATH="/packages/peripherals/hal-sdk/at32/at32f403a_407_hal_driver"
   CONFIG_PKG_USING_AT32F403A_407_HAL_DRIVER_LATEST_VERSION=y
   CONFIG_PKG_AT32F403A_407_HAL_DRIVER_VER="latest"
   CONFIG_PKG_USING_AT32F403A_407_CMSIS_DRIVER=y
   CONFIG_PKG_AT32F403A_407_CMSIS_DRIVER_PATH="/packages/peripherals/hal-sdk/at32/at32f403a_407_cmsis_driver"
   CONFIG_PKG_USING_AT32F403A_407_CMSIS_DRIVER_LATEST_VERSION=y
   ```

2. 将期望bsp下的`borad`文件夹下的所有文件替换掉现有的

3. 更改template.uvprojx选的mcu，这个keil会根据他自动生成一个选择的mcu同名宏，如：`AT32F403AVG`就会生成一个`AT32F403AVG`的同名宏

   