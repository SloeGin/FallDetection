################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/KalmanFilterTracker.cpp \
../src/MixtureOfGaussianV2BGS.cpp \
../src/RectReg.cpp \
../src/Threat.cpp \
../src/main.cpp 

OBJS += \
./src/KalmanFilterTracker.o \
./src/MixtureOfGaussianV2BGS.o \
./src/RectReg.o \
./src/Threat.o \
./src/main.o 

CPP_DEPS += \
./src/KalmanFilterTracker.d \
./src/MixtureOfGaussianV2BGS.d \
./src/RectReg.d \
./src/Threat.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


