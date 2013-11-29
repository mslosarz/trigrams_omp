################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/InMemoryFile.cpp \
../src/TrigramProcessor.cpp \
../src/trigram_omp.cpp 

OBJS += \
./src/InMemoryFile.o \
./src/TrigramProcessor.o \
./src/trigram_omp.o 

CPP_DEPS += \
./src/InMemoryFile.d \
./src/TrigramProcessor.d \
./src/trigram_omp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -fopenmp -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


