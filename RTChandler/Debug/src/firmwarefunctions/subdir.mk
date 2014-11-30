################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/johannes/git/firmware/src/functions/AOUT_LTC2635.c \
/home/johannes/git/firmware/src/functions/GPIO.c \
/home/johannes/git/firmware/src/functions/I2C-handler.c \
/home/johannes/git/firmware/src/functions/RTC_MCP7940N.c \
/home/johannes/git/firmware/src/functions/common.c 

OBJS += \
./src/firmwarefunctions/AOUT_LTC2635.o \
./src/firmwarefunctions/GPIO.o \
./src/firmwarefunctions/I2C-handler.o \
./src/firmwarefunctions/RTC_MCP7940N.o \
./src/firmwarefunctions/common.o 

C_DEPS += \
./src/firmwarefunctions/AOUT_LTC2635.d \
./src/firmwarefunctions/GPIO.d \
./src/firmwarefunctions/I2C-handler.d \
./src/firmwarefunctions/RTC_MCP7940N.d \
./src/firmwarefunctions/common.d 


# Each subdirectory must supply rules for building sources it contributes
src/firmwarefunctions/AOUT_LTC2635.o: /home/johannes/git/firmware/src/functions/AOUT_LTC2635.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/firmwarefunctions/GPIO.o: /home/johannes/git/firmware/src/functions/GPIO.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/firmwarefunctions/I2C-handler.o: /home/johannes/git/firmware/src/functions/I2C-handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/firmwarefunctions/RTC_MCP7940N.o: /home/johannes/git/firmware/src/functions/RTC_MCP7940N.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/firmwarefunctions/common.o: /home/johannes/git/firmware/src/functions/common.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabi-gcc -I/usr/arm-linux-gnueabi/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


