set(CMAKE_SYSTEM_NAME               Generic)	# target system name, by default same as CMAKE_HOST_SYSTEM_NAME
set(CMAKE_SYSTEM_PROCESSOR          arm)		# target processor, by default same as CMAKE_HOST_SYSTEM_PROCESSOR

set(CMAKE_C_COMPILER_ID GNU)					# C compiler ID
set(CMAKE_CXX_COMPILER_ID GNU)					# C++ compiler ID

# Some default GCC settings
# arm-none-eabi- must be part of path environment
set(TOOLCHAIN_PREFIX                arm-none-eabi-)				

set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)			
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY                   ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE                      ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM     ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C       ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX     ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)		# try_compile target type for cross-compiling

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m3 ")					
# set(CPU_FLAGS "-mcpu=cortex-m3 -mthumb")
# set(FPU_FLAGS "-mfpu=fpv4-sp-d16")
# set(FLOAT_ABI "-mfloat-abi=soft")		

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
# Treat the input file as assembly language, but run it through the C preprocessor first. (-x assembler-with-cpp)
# generate dependency information, not include system header files(-MMD)
# Add phony targets for each dependency in the generated .d file (-MP)
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp -MMD -MP")
# Basic common warnings. (-Wall)
# Additional useful warnings. (-Wextra)
# Strict ISO standard checking. (-Wpedantic)
# Place each function or data item into its own section in the output file (-fdata-sections -ffunction-sections)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -fdata-sections -ffunction-sections")

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-Os -g0")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -g0")
# Disable Run-Time Type Information (-fno-rtti)
# Disable C++ exception handling. (-fno-exceptions)
# Disable thread-safe initialization of static local variables. (-fno-threadsafe-statics)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")

set(CMAKE_C_LINK_FLAGS "${TARGET_FLAGS}")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${CMAKE_SOURCE_DIR}/STM32F103XX_FLASH.ld\"")
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} --specs=nano.specs")			# use newlib-nano
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")	# garbage collection
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lc -lm -Wl,--end-group")		# loop search C	lib
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

set(CMAKE_CXX_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group")	# loop search C++ lib