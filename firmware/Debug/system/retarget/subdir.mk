################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/retarget/_assert.c \
../system/retarget/_exit.c \
../system/retarget/_sbrk.c \
../system/retarget/_stdio.c 

CPP_SRCS += \
../system/retarget/_cxx.cpp 

OBJS += \
./system/retarget/_assert.o \
./system/retarget/_cxx.o \
./system/retarget/_exit.o \
./system/retarget/_sbrk.o \
./system/retarget/_stdio.o 

C_DEPS += \
./system/retarget/_assert.d \
./system/retarget/_exit.d \
./system/retarget/_sbrk.d \
./system/retarget/_stdio.d 

CPP_DEPS += \
./system/retarget/_cxx.d 


# Each subdirectory must supply rules for building sources it contributes
system/retarget/%.o: ../system/retarget/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/retarget/%.o: ../system/retarget/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -std=gnu++14 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


