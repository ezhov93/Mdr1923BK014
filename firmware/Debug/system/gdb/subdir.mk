################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/gdb/arm_stub.c \
../system/gdb/config_gdb.c \
../system/gdb/cortexm_stub.c \
../system/gdb/gdb_stub.c \
../system/gdb/hal_stub.c 

CPP_SRCS += \
../system/gdb/gdb.cpp 

S_UPPER_SRCS += \
../system/gdb/hard_fault_handler.S 

OBJS += \
./system/gdb/arm_stub.o \
./system/gdb/config_gdb.o \
./system/gdb/cortexm_stub.o \
./system/gdb/gdb.o \
./system/gdb/gdb_stub.o \
./system/gdb/hal_stub.o \
./system/gdb/hard_fault_handler.o 

S_UPPER_DEPS += \
./system/gdb/hard_fault_handler.d 

C_DEPS += \
./system/gdb/arm_stub.d \
./system/gdb/config_gdb.d \
./system/gdb/cortexm_stub.d \
./system/gdb/gdb_stub.d \
./system/gdb/hal_stub.d 

CPP_DEPS += \
./system/gdb/gdb.d 


# Each subdirectory must supply rules for building sources it contributes
system/gdb/%.o: ../system/gdb/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/gdb/%.o: ../system/gdb/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -std=gnu++14 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/gdb/%.o: ../system/gdb/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -x assembler-with-cpp -DDEBUG -DUSE_FULL_ASSERT -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system" -I"D:\MEGA\Projects\global\Mdr1923BK014\firmware\system\gdb" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


