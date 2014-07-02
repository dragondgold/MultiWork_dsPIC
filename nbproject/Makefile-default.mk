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
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Main.c LogicAnalizer.c mylibs.c Frecuencimetro.c LC_Meter.c RunLengthAlgorithm.c DataSample.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Main.o ${OBJECTDIR}/LogicAnalizer.o ${OBJECTDIR}/mylibs.o ${OBJECTDIR}/Frecuencimetro.o ${OBJECTDIR}/LC_Meter.o ${OBJECTDIR}/RunLengthAlgorithm.o ${OBJECTDIR}/DataSample.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Main.o.d ${OBJECTDIR}/LogicAnalizer.o.d ${OBJECTDIR}/mylibs.o.d ${OBJECTDIR}/Frecuencimetro.o.d ${OBJECTDIR}/LC_Meter.o.d ${OBJECTDIR}/RunLengthAlgorithm.o.d ${OBJECTDIR}/DataSample.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Main.o ${OBJECTDIR}/LogicAnalizer.o ${OBJECTDIR}/mylibs.o ${OBJECTDIR}/Frecuencimetro.o ${OBJECTDIR}/LC_Meter.o ${OBJECTDIR}/RunLengthAlgorithm.o ${OBJECTDIR}/DataSample.o

# Source Files
SOURCEFILES=Main.c LogicAnalizer.c mylibs.c Frecuencimetro.c LC_Meter.c RunLengthAlgorithm.c DataSample.c


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128GP802
MP_LINKER_FILE_OPTION=,--script=p33FJ128GP802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/LogicAnalizer.o: LogicAnalizer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/LogicAnalizer.o.d 
	@${RM} ${OBJECTDIR}/LogicAnalizer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LogicAnalizer.c  -o ${OBJECTDIR}/LogicAnalizer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LogicAnalizer.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/LogicAnalizer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mylibs.o: mylibs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/mylibs.o.d 
	@${RM} ${OBJECTDIR}/mylibs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mylibs.c  -o ${OBJECTDIR}/mylibs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mylibs.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mylibs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Frecuencimetro.o: Frecuencimetro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Frecuencimetro.o.d 
	@${RM} ${OBJECTDIR}/Frecuencimetro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Frecuencimetro.c  -o ${OBJECTDIR}/Frecuencimetro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Frecuencimetro.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Frecuencimetro.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/LC_Meter.o: LC_Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/LC_Meter.o.d 
	@${RM} ${OBJECTDIR}/LC_Meter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LC_Meter.c  -o ${OBJECTDIR}/LC_Meter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LC_Meter.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/LC_Meter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/RunLengthAlgorithm.o: RunLengthAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RunLengthAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/RunLengthAlgorithm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RunLengthAlgorithm.c  -o ${OBJECTDIR}/RunLengthAlgorithm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/RunLengthAlgorithm.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/RunLengthAlgorithm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DataSample.o: DataSample.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DataSample.o.d 
	@${RM} ${OBJECTDIR}/DataSample.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DataSample.c  -o ${OBJECTDIR}/DataSample.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DataSample.o.d"      -g -D__DEBUG     -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/DataSample.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/Main.o: Main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Main.o.d 
	@${RM} ${OBJECTDIR}/Main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Main.c  -o ${OBJECTDIR}/Main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Main.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/LogicAnalizer.o: LogicAnalizer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/LogicAnalizer.o.d 
	@${RM} ${OBJECTDIR}/LogicAnalizer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LogicAnalizer.c  -o ${OBJECTDIR}/LogicAnalizer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LogicAnalizer.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/LogicAnalizer.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/mylibs.o: mylibs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/mylibs.o.d 
	@${RM} ${OBJECTDIR}/mylibs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  mylibs.c  -o ${OBJECTDIR}/mylibs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/mylibs.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/mylibs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/Frecuencimetro.o: Frecuencimetro.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/Frecuencimetro.o.d 
	@${RM} ${OBJECTDIR}/Frecuencimetro.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Frecuencimetro.c  -o ${OBJECTDIR}/Frecuencimetro.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/Frecuencimetro.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/Frecuencimetro.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/LC_Meter.o: LC_Meter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/LC_Meter.o.d 
	@${RM} ${OBJECTDIR}/LC_Meter.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  LC_Meter.c  -o ${OBJECTDIR}/LC_Meter.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/LC_Meter.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/LC_Meter.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/RunLengthAlgorithm.o: RunLengthAlgorithm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/RunLengthAlgorithm.o.d 
	@${RM} ${OBJECTDIR}/RunLengthAlgorithm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RunLengthAlgorithm.c  -o ${OBJECTDIR}/RunLengthAlgorithm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/RunLengthAlgorithm.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/RunLengthAlgorithm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/DataSample.o: DataSample.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/DataSample.o.d 
	@${RM} ${OBJECTDIR}/DataSample.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  DataSample.c  -o ${OBJECTDIR}/DataSample.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/DataSample.o.d"        -g -omf=coff -O0 -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/DataSample.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG   -omf=coff -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MultiWork_dsPIC.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff 
	
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
