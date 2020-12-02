################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PedsXmlCollectionProcessor.cpp \
../src/PedsXsltProcessor.cpp \
../src/Proca.cpp \
../src/Procf.cpp \
../src/Proco.cpp \
../src/SystemXsltProcessor.cpp \
../src/main.cpp 

OBJS += \
./src/PedsXmlCollectionProcessor.o \
./src/PedsXsltProcessor.o \
./src/Proca.o \
./src/Procf.o \
./src/Proco.o \
./src/SystemXsltProcessor.o \
./src/main.o 

CPP_DEPS += \
./src/PedsXmlCollectionProcessor.d \
./src/PedsXsltProcessor.d \
./src/Proca.d \
./src/Procf.d \
./src/Proco.d \
./src/SystemXsltProcessor.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/libxml2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


