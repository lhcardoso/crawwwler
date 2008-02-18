################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Http/HttpUtils/HttpHeader.cpp \
../Http/HttpUtils/HttpRequest.cpp \
../Http/HttpUtils/HttpResponse.cpp 

OBJS += \
./Http/HttpUtils/HttpHeader.o \
./Http/HttpUtils/HttpRequest.o \
./Http/HttpUtils/HttpResponse.o 

CPP_DEPS += \
./Http/HttpUtils/HttpHeader.d \
./Http/HttpUtils/HttpRequest.d \
./Http/HttpUtils/HttpResponse.d 


# Each subdirectory must supply rules for building sources it contributes
Http/HttpUtils/%.o: ../Http/HttpUtils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


