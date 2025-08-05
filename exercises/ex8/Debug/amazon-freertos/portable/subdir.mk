################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amazon-freertos/portable/heap_4.c 

OBJS += \
./amazon-freertos/portable/heap_4.o 

C_DEPS += \
./amazon-freertos/portable/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
amazon-freertos/portable/%.o: ../amazon-freertos/portable/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I"C:\Users\dhowlett\Documents\MCUXpressoIDE_10.3.0_2200\workspace\ex11_ans\amazon-freertos\FreeRTOS\portable" -I../freertos/portable -I../amazon-freertos/include -I../startup -I../CMSIS -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


