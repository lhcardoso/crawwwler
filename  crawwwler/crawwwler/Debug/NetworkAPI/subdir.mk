################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../NetworkAPI/Port.cpp \
../NetworkAPI/Socket.cpp 

OBJS += \
./NetworkAPI/Port.o \
./NetworkAPI/Socket.o 

CPP_DEPS += \
./NetworkAPI/Port.d \
./NetworkAPI/Socket.d 


# Each subdirectory must supply rules for building sources it contributes
NetworkAPI/%.o: ../NetworkAPI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


