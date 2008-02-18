################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Url/ManagedUrlList.cpp \
../Url/Url.cpp 

OBJS += \
./Url/ManagedUrlList.o \
./Url/Url.o 

CPP_DEPS += \
./Url/ManagedUrlList.d \
./Url/Url.d 


# Each subdirectory must supply rules for building sources it contributes
Url/%.o: ../Url/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


