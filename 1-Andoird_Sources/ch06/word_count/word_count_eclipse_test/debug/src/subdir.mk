################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/root/drivers/ch06/word_count/test_word_count.c 

OBJS += \
./src/test_word_count.o 

C_DEPS += \
./src/test_word_count.d 


# Each subdirectory must supply rules for building sources it contributes
src/test_word_count.o: /root/drivers/ch06/word_count/test_word_count.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


