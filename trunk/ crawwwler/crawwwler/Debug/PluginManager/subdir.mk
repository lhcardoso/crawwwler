################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../PluginManager/Plugin.cpp \
../PluginManager/PluginId.cpp 

OBJS += \
./PluginManager/Plugin.o \
./PluginManager/PluginId.o 

CPP_DEPS += \
./PluginManager/Plugin.d \
./PluginManager/PluginId.d 


# Each subdirectory must supply rules for building sources it contributes
PluginManager/%.o: ../PluginManager/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


