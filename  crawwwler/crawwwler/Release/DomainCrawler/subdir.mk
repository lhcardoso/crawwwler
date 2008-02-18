################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DomainCrawler/DomainCrawler.cpp 

OBJS += \
./DomainCrawler/DomainCrawler.o 

CPP_DEPS += \
./DomainCrawler/DomainCrawler.d 


# Each subdirectory must supply rules for building sources it contributes
DomainCrawler/%.o: ../DomainCrawler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


