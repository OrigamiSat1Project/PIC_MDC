#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
<<<<<<< HEAD
SOURCEFILES_QUOTED_IF_SPACED=CAN.c I2Clib.c init.c interrupt.c ADC.c MPU9250.c PWM.c EEPROM.c SMA.c PIC_MDC.c interrupt.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/CAN.p1 ${OBJECTDIR}/I2Clib.p1 ${OBJECTDIR}/init.p1 ${OBJECTDIR}/interrupt.p1 ${OBJECTDIR}/ADC.p1 ${OBJECTDIR}/MPU9250.p1 ${OBJECTDIR}/PWM.p1 ${OBJECTDIR}/EEPROM.p1 ${OBJECTDIR}/SMA.p1 ${OBJECTDIR}/PIC_MDC.p1 ${OBJECTDIR}/interrupt.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/CAN.p1.d ${OBJECTDIR}/I2Clib.p1.d ${OBJECTDIR}/init.p1.d ${OBJECTDIR}/interrupt.p1.d ${OBJECTDIR}/ADC.p1.d ${OBJECTDIR}/MPU9250.p1.d ${OBJECTDIR}/PWM.p1.d ${OBJECTDIR}/EEPROM.p1.d ${OBJECTDIR}/SMA.p1.d ${OBJECTDIR}/PIC_MDC.p1.d ${OBJECTDIR}/interrupt.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/CAN.p1 ${OBJECTDIR}/I2Clib.p1 ${OBJECTDIR}/init.p1 ${OBJECTDIR}/interrupt.p1 ${OBJECTDIR}/ADC.p1 ${OBJECTDIR}/MPU9250.p1 ${OBJECTDIR}/PWM.p1 ${OBJECTDIR}/EEPROM.p1 ${OBJECTDIR}/SMA.p1 ${OBJECTDIR}/PIC_MDC.p1 ${OBJECTDIR}/interrupt.p1

# Source Files
SOURCEFILES=CAN.c I2Clib.c init.c interrupt.c ADC.c MPU9250.c PWM.c EEPROM.c SMA.c PIC_MDC.c interrupt.c
=======
SOURCEFILES_QUOTED_IF_SPACED=CAN.c I2Clib.c init.c ADC.c MPU9250.c PWM.c EEPROM.c SMA.c PIC_MDC.c Timer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/CAN.p1 ${OBJECTDIR}/I2Clib.p1 ${OBJECTDIR}/init.p1 ${OBJECTDIR}/ADC.p1 ${OBJECTDIR}/MPU9250.p1 ${OBJECTDIR}/PWM.p1 ${OBJECTDIR}/EEPROM.p1 ${OBJECTDIR}/SMA.p1 ${OBJECTDIR}/PIC_MDC.p1 ${OBJECTDIR}/Timer.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/CAN.p1.d ${OBJECTDIR}/I2Clib.p1.d ${OBJECTDIR}/init.p1.d ${OBJECTDIR}/ADC.p1.d ${OBJECTDIR}/MPU9250.p1.d ${OBJECTDIR}/PWM.p1.d ${OBJECTDIR}/EEPROM.p1.d ${OBJECTDIR}/SMA.p1.d ${OBJECTDIR}/PIC_MDC.p1.d ${OBJECTDIR}/Timer.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/CAN.p1 ${OBJECTDIR}/I2Clib.p1 ${OBJECTDIR}/init.p1 ${OBJECTDIR}/ADC.p1 ${OBJECTDIR}/MPU9250.p1 ${OBJECTDIR}/PWM.p1 ${OBJECTDIR}/EEPROM.p1 ${OBJECTDIR}/SMA.p1 ${OBJECTDIR}/PIC_MDC.p1 ${OBJECTDIR}/Timer.p1

# Source Files
SOURCEFILES=CAN.c I2Clib.c init.c ADC.c MPU9250.c PWM.c EEPROM.c SMA.c PIC_MDC.c Timer.c
>>>>>>> Timer_dev


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F25K80
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/CAN.p1: CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CAN.p1.d 
	@${RM} ${OBJECTDIR}/CAN.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/CAN.p1  CAN.c 
	@-${MV} ${OBJECTDIR}/CAN.d ${OBJECTDIR}/CAN.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/CAN.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2Clib.p1: I2Clib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2Clib.p1.d 
	@${RM} ${OBJECTDIR}/I2Clib.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/I2Clib.p1  I2Clib.c 
	@-${MV} ${OBJECTDIR}/I2Clib.d ${OBJECTDIR}/I2Clib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2Clib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/init.p1: init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init.p1.d 
	@${RM} ${OBJECTDIR}/init.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/init.p1  init.c 
	@-${MV} ${OBJECTDIR}/init.d ${OBJECTDIR}/init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ADC.p1: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.p1.d 
	@${RM} ${OBJECTDIR}/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ADC.p1  ADC.c 
	@-${MV} ${OBJECTDIR}/ADC.d ${OBJECTDIR}/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MPU9250.p1: MPU9250.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MPU9250.p1.d 
	@${RM} ${OBJECTDIR}/MPU9250.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MPU9250.p1  MPU9250.c 
	@-${MV} ${OBJECTDIR}/MPU9250.d ${OBJECTDIR}/MPU9250.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MPU9250.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PWM.p1: PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PWM.p1.d 
	@${RM} ${OBJECTDIR}/PWM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PWM.p1  PWM.c 
	@-${MV} ${OBJECTDIR}/PWM.d ${OBJECTDIR}/PWM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PWM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/EEPROM.p1: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/EEPROM.p1  EEPROM.c 
	@-${MV} ${OBJECTDIR}/EEPROM.d ${OBJECTDIR}/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SMA.p1: SMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SMA.p1.d 
	@${RM} ${OBJECTDIR}/SMA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SMA.p1  SMA.c 
	@-${MV} ${OBJECTDIR}/SMA.d ${OBJECTDIR}/SMA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SMA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PIC_MDC.p1: PIC_MDC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_MDC.p1.d 
	@${RM} ${OBJECTDIR}/PIC_MDC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PIC_MDC.p1  PIC_MDC.c 
	@-${MV} ${OBJECTDIR}/PIC_MDC.d ${OBJECTDIR}/PIC_MDC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PIC_MDC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
<<<<<<< HEAD
${OBJECTDIR}/interrupt.p1: interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupt.p1  interrupt.c 
	@-${MV} ${OBJECTDIR}/interrupt.d ${OBJECTDIR}/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
=======
${OBJECTDIR}/Timer.p1: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer.p1.d 
	@${RM} ${OBJECTDIR}/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Timer.p1  Timer.c 
	@-${MV} ${OBJECTDIR}/Timer.d ${OBJECTDIR}/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
>>>>>>> Timer_dev
	
else
${OBJECTDIR}/CAN.p1: CAN.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CAN.p1.d 
	@${RM} ${OBJECTDIR}/CAN.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/CAN.p1  CAN.c 
	@-${MV} ${OBJECTDIR}/CAN.d ${OBJECTDIR}/CAN.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/CAN.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/I2Clib.p1: I2Clib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2Clib.p1.d 
	@${RM} ${OBJECTDIR}/I2Clib.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/I2Clib.p1  I2Clib.c 
	@-${MV} ${OBJECTDIR}/I2Clib.d ${OBJECTDIR}/I2Clib.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/I2Clib.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/init.p1: init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/init.p1.d 
	@${RM} ${OBJECTDIR}/init.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/init.p1  init.c 
	@-${MV} ${OBJECTDIR}/init.d ${OBJECTDIR}/init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ADC.p1: ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.p1.d 
	@${RM} ${OBJECTDIR}/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/ADC.p1  ADC.c 
	@-${MV} ${OBJECTDIR}/ADC.d ${OBJECTDIR}/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MPU9250.p1: MPU9250.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MPU9250.p1.d 
	@${RM} ${OBJECTDIR}/MPU9250.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/MPU9250.p1  MPU9250.c 
	@-${MV} ${OBJECTDIR}/MPU9250.d ${OBJECTDIR}/MPU9250.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MPU9250.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PWM.p1: PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PWM.p1.d 
	@${RM} ${OBJECTDIR}/PWM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PWM.p1  PWM.c 
	@-${MV} ${OBJECTDIR}/PWM.d ${OBJECTDIR}/PWM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PWM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/EEPROM.p1: EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EEPROM.p1.d 
	@${RM} ${OBJECTDIR}/EEPROM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/EEPROM.p1  EEPROM.c 
	@-${MV} ${OBJECTDIR}/EEPROM.d ${OBJECTDIR}/EEPROM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/EEPROM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/SMA.p1: SMA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SMA.p1.d 
	@${RM} ${OBJECTDIR}/SMA.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/SMA.p1  SMA.c 
	@-${MV} ${OBJECTDIR}/SMA.d ${OBJECTDIR}/SMA.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/SMA.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/PIC_MDC.p1: PIC_MDC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC_MDC.p1.d 
	@${RM} ${OBJECTDIR}/PIC_MDC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/PIC_MDC.p1  PIC_MDC.c 
	@-${MV} ${OBJECTDIR}/PIC_MDC.d ${OBJECTDIR}/PIC_MDC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/PIC_MDC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
<<<<<<< HEAD
${OBJECTDIR}/interrupt.p1: interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupt.p1.d 
	@${RM} ${OBJECTDIR}/interrupt.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/interrupt.p1  interrupt.c 
	@-${MV} ${OBJECTDIR}/interrupt.d ${OBJECTDIR}/interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
=======
${OBJECTDIR}/Timer.p1: Timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer.p1.d 
	@${RM} ${OBJECTDIR}/Timer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/Timer.p1  Timer.c 
	@-${MV} ${OBJECTDIR}/Timer.d ${OBJECTDIR}/Timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/Timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
>>>>>>> Timer_dev
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=icd3  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=+asm,+asmfile,-speed,+space,-debug,-local --addrqual=ignore --mode=free -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,-plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/PIC_MDC.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
