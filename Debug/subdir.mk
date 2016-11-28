################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cr_startup_lpc17.c \
../lightSensor.c \
../main.c \
../startOled.c 

OBJS += \
./cr_startup_lpc17.o \
./lightSensor.o \
./main.o \
./startOled.o 

C_DEPS += \
./cr_startup_lpc17.d \
./lightSensor.d \
./main.d \
./startOled.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\Luiz\Downloads\source-code-for-LPC17xx-examples\FreeRTOS_Source\demo_code" -I"C:\Users\Luiz\Downloads\source-code-for-LPC17xx-examples\CMSISv1p30_LPC17xx\inc" -I"C:\Users\Luiz\Downloads\source-code-for-LPC17xx-examples\FreeRTOS_Source\include" -I"C:\Users\Luiz\Downloads\source-code-for-LPC17xx-examples\FreeRTOS_Source\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


