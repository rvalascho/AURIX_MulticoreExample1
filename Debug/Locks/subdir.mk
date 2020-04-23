################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Locks/lock_example.c \
../Locks/util.c 

OBJS += \
./Locks/lock_example.o \
./Locks/util.o 

COMPILED_SRCS += \
./Locks/lock_example.src \
./Locks/util.src 

C_DEPS += \
./Locks/lock_example.d \
./Locks/util.d 


# Each subdirectory must supply rules for building sources it contributes
Locks/%.src: ../Locks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C Compiler'
	ctc -I../Libraries/iLLD/TC27D/Tricore/_PinMap -I../Libraries/Infra/Platform/Tricore/Compilers -I../Libraries/iLLD/TC27D/Tricore/Ccu6/Icu -I../Libraries/iLLD/TC27D/Tricore/I2c/Std -I../Libraries/Infra/Platform -I../Libraries/iLLD/TC27D/Tricore/Msc/Msc -I../Libraries/Service/CpuGeneric/If/Ccu6If -I../Libraries/iLLD/TC27D/Tricore/Qspi/Std -I../Libraries/iLLD/TC27D/Tricore/Cif -I../Libraries/iLLD/TC27D/Tricore/Eth/Std -I../Libraries/iLLD/TC27D/Tricore/Flash -I../Libraries/iLLD/TC27D/Tricore/_Lib/DataHandling -I../Libraries/Service/CpuGeneric/SysSe/Comm -I../Libraries/Service/CpuGeneric/SysSe/Math -I../Libraries/Infra/Platform/Tricore -I../Libraries/iLLD/TC27D/Tricore/Dsadc/Dsadc -I../Libraries/iLLD/TC27D/Tricore/Vadc/Std -I../Libraries/iLLD/TC27D/Tricore/Sent -I../Libraries/iLLD/TC27D/Tricore/Qspi -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tom -I../Libraries/iLLD/TC27D/Tricore/Iom/Std -I../Libraries/iLLD/TC27D/Tricore/Multican/Can -I../Libraries/iLLD/TC27D/Tricore/Dma/Dma -I../Libraries/Infra -I../Libraries/iLLD/TC27D/Tricore/Gpt12 -I../Libraries/iLLD/TC27D/Tricore/Stm/Std -I../Libraries/iLLD/TC27D/Tricore/Eray -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tom/Pwm -I../Libraries/iLLD/TC27D/Tricore/Hssl -I../Libraries/iLLD/TC27D/Tricore/Mtu -I../Libraries/iLLD/TC27D/Tricore/_Impl -I../Libraries/iLLD/TC27D/Tricore/Eth/Phy_Pef7071 -I../Libraries/Service/CpuGeneric/SysSe -I../Libraries/iLLD/TC27D/Tricore/Scu/Std -I../Libraries/iLLD/TC27D/Tricore/Iom/Driver -I../Libraries/iLLD/TC27D/Tricore/Stm/Timer -I../Libraries/iLLD/TC27D/Tricore/_Lib -I../Libraries/iLLD/TC27D/Tricore/Sent/Std -I../Libraries/iLLD/TC27D/Tricore/Gtm/Atom/Timer -I../Libraries/Service/CpuGeneric/If -I../Libraries/iLLD/TC27D/Tricore/Cpu -I../Libraries/iLLD/TC27D/Tricore/Dsadc -I../Libraries/iLLD/TC27D/Tricore/Cpu/Trap -I../Libraries/iLLD/TC27D/Tricore/Asclin -I../Libraries/iLLD/TC27D/Tricore/Emem/Std -I../Libraries/iLLD/TC27D/Tricore/Psi5 -I../Libraries/iLLD/TC27D/Tricore/Hssl/Hssl -I../Libraries/iLLD/TC27D/Tricore/Multican/Std -I../Libraries/iLLD/TC27D/Tricore/Dts/Dts -I../Libraries/iLLD/TC27D/Tricore/Eth -I../Libraries/iLLD/TC27D/Tricore/Emem -I../Libraries/iLLD/TC27D/Tricore/Multican -I../Libraries/iLLD/TC27D/Tricore/Psi5/Psi5 -I../Libraries/iLLD/TC27D/Tricore/Cpu/CStart -I../Libraries/iLLD/TC27D/Tricore/Gpt12/Std -I../Libraries/iLLD/TC27D/Tricore/Msc -I../Libraries/iLLD/TC27D/Tricore/Qspi/SpiSlave -I../Libraries/iLLD/TC27D/Tricore/Asclin/Std -I../Libraries/iLLD/TC27D/Tricore/Flash/Std -I../Libraries/iLLD/TC27D/Tricore -I../Libraries/iLLD/TC27D/Tricore/Dsadc/Std -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tom/PwmHl -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tim -I../Libraries/iLLD/TC27D/Tricore/Fce/Crc -I../Libraries/iLLD/TC27D/Tricore/I2c -I../Libraries/iLLD/TC27D/Tricore/Vadc -I../Libraries/iLLD/TC27D/Tricore/Ccu6/Timer -I../Libraries/Infra/Sfr -I../Libraries/iLLD/TC27D/Tricore/Cif/Cam -I../Libraries/iLLD/TC27D/Tricore/Eray/Eray -I../Libraries/Service/CpuGeneric/SysSe/Bsp -I../Libraries/Service/CpuGeneric/SysSe/General -I../Libraries/iLLD/TC27D/Tricore/Src/Std -I../Libraries/Infra/Sfr/TC27D/_Reg -I../Libraries/iLLD/TC27D/Tricore/Port -I../Libraries/iLLD/TC27D/Tricore/Dma/Std -I../Configurations -I../Libraries/iLLD/TC27D/Tricore/Cpu/Std -I../Libraries/iLLD/TC27D -I../Libraries/iLLD/TC27D/Tricore/Qspi/SpiMaster -I../Libraries/iLLD/TC27D/Tricore/Dts/Std -I../Libraries/iLLD/TC27D/Tricore/Gtm/Atom -I../Libraries/iLLD/TC27D/Tricore/Smu -I../Libraries/Infra/Sfr/TC27D -I../Libraries/iLLD/TC27D/Tricore/Asclin/Asc -I../Libraries/iLLD/TC27D/Tricore/Sent/Sent -I../Libraries/iLLD/TC27D/Tricore/Vadc/Adc -I../Libraries/iLLD/TC27D/Tricore/Fce -I../Libraries/iLLD/TC27D/Tricore/Port/Std -I../Libraries/iLLD/TC27D/Tricore/Psi5s/Std -I../Libraries/Service/CpuGeneric -I../Libraries/iLLD/TC27D/Tricore/Psi5s/Psi5s -I../Libraries/iLLD/TC27D/Tricore/Stm -I../Libraries/iLLD/TC27D/Tricore/Mtu/Std -I../Libraries/Service/CpuGeneric/SysSe/Time -I../Libraries/iLLD/TC27D/Tricore/Gtm -I../Libraries/iLLD -I../Libraries/iLLD/TC27D/Tricore/Ccu6/PwmHl -I../Libraries/iLLD/TC27D/Tricore/Cpu/Irq -I../Libraries/iLLD/TC27D/Tricore/Psi5/Std -I../Libraries/iLLD/TC27D/Tricore/_Lib/InternalMux -I../Libraries/iLLD/TC27D/Tricore/Fce/Std -I../Libraries/iLLD/TC27D/Tricore/Gtm/Atom/Pwm -I../Libraries/iLLD/TC27D/Tricore/Psi5s -I../Libraries/iLLD/TC27D/Tricore/Scu -I../Libraries/iLLD/TC27D/Tricore/Gtm/Trig -I../Libraries/iLLD/TC27D/Tricore/Ccu6/TimerWithTrigger -I../Libraries/Service -I../Libraries/iLLD/TC27D/Tricore/Cif/Std -I../Libraries/iLLD/TC27D/Tricore/Eray/Std -I../Libraries/Service/CpuGeneric/StdIf -I../Libraries/iLLD/TC27D/Tricore/Asclin/Spi -I../Libraries/iLLD/TC27D/Tricore/Hssl/Std -I../Libraries/iLLD/TC27D/Tricore/Ccu6 -I../Libraries/iLLD/TC27D/Tricore/I2c/I2c -I../Libraries/iLLD/TC27D/Tricore/Iom -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tom/Timer -I../Libraries/iLLD/TC27D/Tricore/Gtm/Atom/PwmHl -I../Libraries/iLLD/TC27D/Tricore/Msc/Std -I../Libraries/Service/CpuGeneric/_Utilities -I../Libraries/iLLD/TC27D/Tricore/Dsadc/Rdc -I../Libraries/iLLD/TC27D/Tricore/Dma -I../Libraries/iLLD/TC27D/Tricore/Asclin/Lin -I../Libraries/iLLD/TC27D/Tricore/Gpt12/IncrEnc -I../Libraries/iLLD/TC27D/Tricore/Gtm/Std -I../Libraries -I../Libraries/iLLD/TC27D/Tricore/Ccu6/PwmBc -I../Libraries/iLLD/TC27D/Tricore/Ccu6/TPwm -I../Libraries/iLLD/TC27D/Tricore/Dts -I../Libraries/iLLD/TC27D/Tricore/Smu/Std -I../Libraries/iLLD/TC27D/Tricore/Gtm/Tim/In -I../Libraries/iLLD/TC27D/Tricore/Src -I../Libraries/iLLD/TC27D/Tricore/Ccu6/Std -I../Libraries/iLLD/TC27D/Tricore/Port/Io -I"C:\Users\valascho\AURIX-v1.1.6-workspace\Multicore_Example1\Locks" -I"C:\Users\valascho\AURIX-v1.1.6-workspace\Multicore_Example1\Drivers" --iso=99 --language=+volatile --fp-model=3 --fp-model=+contract --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g --no-warnings=544,557 -o "$@"  "$<"  --core=tc1.6.x --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

Locks/%.o: ./Locks/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  $@ $(@:.o=.src) --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


