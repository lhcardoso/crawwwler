################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Utils/GlobalData/GlobalData.cpp 

OBJS += \
./Utils/GlobalData/GlobalData.o 

CPP_DEPS += \
./Utils/GlobalData/GlobalData.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/GlobalData/%.o: ../Utils/GlobalData/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


