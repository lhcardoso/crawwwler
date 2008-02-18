################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Http/HttpConnector/HttpClient.cpp 

OBJS += \
./Http/HttpConnector/HttpClient.o 

CPP_DEPS += \
./Http/HttpConnector/HttpClient.d 


# Each subdirectory must supply rules for building sources it contributes
Http/HttpConnector/%.o: ../Http/HttpConnector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


