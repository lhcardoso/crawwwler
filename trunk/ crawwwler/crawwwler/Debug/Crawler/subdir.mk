################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Crawler/CrawlerPlugin.cpp 

OBJS += \
./Crawler/CrawlerPlugin.o 

CPP_DEPS += \
./Crawler/CrawlerPlugin.d 


# Each subdirectory must supply rules for building sources it contributes
Crawler/%.o: ../Crawler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


