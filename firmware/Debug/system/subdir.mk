################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/_initialize_hardware.c \
../system/_reset_hardware.c \
../system/exception_handlers.c 

OBJS += \
./system/_initialize_hardware.o \
./system/_reset_hardware.o \
./system/exception_handlers.o 

C_DEPS += \
./system/_initialize_hardware.d \
./system/_reset_hardware.d \
./system/exception_handlers.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -I"../include" -I../system -I../system/gdb -I../system/1923VK014 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


