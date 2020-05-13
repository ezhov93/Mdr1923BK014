################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/system_1923VK014.c 

S_UPPER_SRCS += \
../system/startup_1923VK014.S 

OBJS += \
./system/startup_1923VK014.o \
./system/system_1923VK014.o 

S_UPPER_DEPS += \
./system/startup_1923VK014.d 

C_DEPS += \
./system/system_1923VK014.d 


# Each subdirectory must supply rules for building sources it contributes
system/%.o: ../system/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/%.o: ../system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


