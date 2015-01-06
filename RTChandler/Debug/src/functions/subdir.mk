################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/johannes/web-plc/firmware/src/functions/AIN-handler.c \
/home/johannes/web-plc/firmware/src/functions/AOUT_LTC2635.c \
/home/johannes/web-plc/firmware/src/functions/GPIO.c \
/home/johannes/web-plc/firmware/src/functions/I2C-handler.c \
/home/johannes/web-plc/firmware/src/functions/RTC_MCP7940N.c \
/home/johannes/web-plc/firmware/src/functions/common.c 

OBJS += \
./src/functions/AIN-handler.o \
./src/functions/AOUT_LTC2635.o \
./src/functions/GPIO.o \
./src/functions/I2C-handler.o \
./src/functions/RTC_MCP7940N.o \
./src/functions/common.o 

C_DEPS += \
./src/functions/AIN-handler.d \
./src/functions/AOUT_LTC2635.d \
./src/functions/GPIO.d \
./src/functions/I2C-handler.d \
./src/functions/RTC_MCP7940N.d \
./src/functions/common.d 


# Each subdirectory must supply rules for building sources it contributes
src/functions/AIN-handler.o: /home/johannes/web-plc/firmware/src/functions/AIN-handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/functions/AOUT_LTC2635.o: /home/johannes/web-plc/firmware/src/functions/AOUT_LTC2635.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/functions/GPIO.o: /home/johannes/web-plc/firmware/src/functions/GPIO.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/functions/I2C-handler.o: /home/johannes/web-plc/firmware/src/functions/I2C-handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/functions/RTC_MCP7940N.o: /home/johannes/web-plc/firmware/src/functions/RTC_MCP7940N.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/functions/common.o: /home/johannes/web-plc/firmware/src/functions/common.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -I/home/johannes/web-plc/firmware/src/functions -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


