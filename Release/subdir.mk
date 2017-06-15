################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GClient.cpp \
../MPDClient.cpp \
../Notification.cpp \
../main.cpp 

OBJS += \
./GClient.o \
./MPDClient.o \
./Notification.o \
./main.o 

CPP_DEPS += \
./GClient.d \
./MPDClient.d \
./Notification.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0  -lmpdclient  `pkg-config --libs --cflags glib-2.0 gtk+-2.0` -lnotify -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


