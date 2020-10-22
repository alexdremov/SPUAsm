# Generated on 2020-10-21 21:12:23 by version 0.9.0 of mulle-xcode-to-cmake
# Command line:
#    mulle-xcode-to-cmake -l c++ -f export SoftProcessorUnit.xcodeproj


cmake_minimum_required (VERSION 3.4)
project( SoftProcessorUnit CXX)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# ###
# Build for mulle-objc (https://mulle-objc.github.io/):
#
#    mulle-sde init -m foundation/objc-porter executable
#    mulle-sde craft
#
# [mulle-clang >= 8.0.0.0 and mulle-objc >= 0.15 required]
#

if( NOT DEPENDENCY_DIR)
   set( DEPENDENCY_DIR "$ENV{DEPENDENCY_DIR}")
endif()
if( NOT DEPENDENCY_DIR)
   set( DEPENDENCY_DIR "${PROJECT_SOURCE_DIR}/dependency")
endif()
if( EXISTS "${DEPENDENCY_DIR}")
   if( NOT ADDICTION_DIR)
      get_filename_component( ADDICTION_DIR "${DEPENDENCY_DIR}" DIRECTORY)
      set( ADDICTION_DIR "${ADDICTION_DIR}/addiction")
   endif()
   set( CMAKE_FIND_FRAMEWORK "LAST")
   include_directories( BEFORE SYSTEM
      ${DEPENDENCY_DIR}/include
      ${ADDICTION_DIR}/include
   )
   set( CMAKE_FRAMEWORK_PATH
      ${DEPENDENCY_DIR}/Frameworks
      ${ADDICTION_DIR}/Frameworks
      ${CMAKE_FRAMEWORK_PATH}
   )
   set( CMAKE_LIBRARY_PATH
      ${DEPENDENCY_DIR}/lib
      ${ADDICTION_DIR}/lib
      ${CMAKE_LIBRARY_PATH}
   )
   set( SKIP_FIND_FOUNDATION_LIBRARY ON)
   execute_process( COMMAND mulle-sde stash-dir
                    OUTPUT_VARIABLE MULLE_SOURCETREE_STASH_DIR)
   string( STRIP "${MULLE_SOURCETREE_STASH_DIR}" MULLE_SOURCETREE_STASH_DIR)
   execute_process( COMMAND mulle-sde linkorder --stash-dir "${MULLE_SOURCETREE_STASH_DIR}" --startup --simplify --output-format cmake
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                    OUTPUT_VARIABLE MULLE_SDE_LINKER_FLAGS
                    RESULT_VARIABLE RVAL)
   if( NOT ${RVAL} EQUAL 0)
      message( FATAL_ERROR "Failed to procure linkorder from mulle-sde. Old version ?")
   endif()
   message( STATUS "MULLE_SDE_LINKER_FLAGS=\"${MULLE_SDE_LINKER_FLAGS}\"")
else()
   message( STATUS "Not a mulle-sde build (\"${DEPENDENCY_DIR}\" does not exist)")
endif()


#
# Platform specific definitions
#

if( APPLE)
   # # CMAKE_OSX_SYSROOT must be set for CMAKE_OSX_DEPLOYMENT_TARGET (cmake bug)
   # if( NOT CMAKE_OSX_SYSROOT)
   #    set( CMAKE_OSX_SYSROOT "/" CACHE STRING "SDK for OSX" FORCE)   # means current OS X
   # endif()
   #
   # # baseline set to 10.6 for rpath
   # if( NOT CMAKE_OSX_DEPLOYMENT_TARGET)
   #   set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6" CACHE STRING "Deployment target for OSX" FORCE)
   # endif()

   set( CMAKE_POSITION_INDEPENDENT_CODE FALSE)
   set( CMAKE_INSTALL_RPATH "@rpath/../lib")

   set( BEGIN_ALL_LOAD "-all_load")
   set( END_ALL_LOAD)
else()
   set( CMAKE_POSITION_INDEPENDENT_CODE TRUE)

   if( WIN32)
   # windows
   else()
   # linux / gcc
      set( BEGIN_ALL_LOAD "-Wl,--whole-archive")
      set( END_ALL_LOAD "-Wl,--no-whole-archive")
      set( CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
   endif()
endif()


##
## SPU Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SPU_SOURCES
SoftProcessorUnit/Assembly/Helpers/AssemblyHelpers.cpp
SoftProcessorUnit/Assembly/Helpers/CommandsParser.cpp
SoftProcessorUnit/Assembly/Helpers/LabelHandlers/LabelsStore.cpp
SoftProcessorUnit/Common/Stack/StackRigid.cpp
SoftProcessorUnit/SPU/Core/SPUCore.cpp
SoftProcessorUnit/SPU/Core/SPUCoreHelpers.cpp
SoftProcessorUnit/SPU/SPU.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/BytecodeToCommand.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/CommandToBytecode.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/InstrExecutors.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/ParseHelpers.cpp
SoftProcessorUnit/Syntax/Translation/Syntax.cpp
)

set( SPU_STATIC_DEPENDENCIES
)

set( SPU_DEPENDENCIES

)


##
## SPUAsm Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SPUASM_SOURCES
SoftProcessorUnit/Assembly/Helpers/AnalysisAndPreparing/CodeAnalysis.cpp
SoftProcessorUnit/Assembly/Helpers/AnalysisAndPreparing/StringDistance.cpp
SoftProcessorUnit/Assembly/Helpers/AssemblyHelpers.cpp
SoftProcessorUnit/Assembly/Helpers/CommandsParser.cpp
SoftProcessorUnit/Assembly/Helpers/LabelHandlers/LabelsStore.cpp
SoftProcessorUnit/Assembly/SPUAssembly.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/BytecodeToCommand.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/CommandToBytecode.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/ParseHelpers.cpp
SoftProcessorUnit/Syntax/Translation/Syntax.cpp
)

set( SPUASM_STATIC_DEPENDENCIES
)

set( SPUASM_DEPENDENCIES

)


##
## SPUDisAsm Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SPUDIS_ASM_SOURCES
SoftProcessorUnit/Assembly/Helpers/AssemblyHelpers.cpp
SoftProcessorUnit/Assembly/Helpers/CommandsParser.cpp
SoftProcessorUnit/Assembly/Helpers/LabelHandlers/LabelsStore.cpp
SoftProcessorUnit/Disassembly/Helpers/DisAssemblyHelpers.cpp
SoftProcessorUnit/Disassembly/SPUDisAssembly.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/BytecodeToCommand.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/CommandToBytecode.cpp
SoftProcessorUnit/Syntax/Translation/Helpers/ParseHelpers.cpp
SoftProcessorUnit/Syntax/Translation/Syntax.cpp
)

set( SPUDIS_ASM_STATIC_DEPENDENCIES
)

set( SPUDIS_ASM_DEPENDENCIES

)

include_directories(
SoftProcessorUnit/
SoftProcessorUnit/Disassembly
SoftProcessorUnit/Disassembly/Helpers
SoftProcessorUnit/Assembly
SoftProcessorUnit/Assembly/Helpers
SoftProcessorUnit/Assembly/Helpers/LabelHandlers
SoftProcessorUnit/Assembly/Helpers/DataTypes
SoftProcessorUnit/Assembly/Helpers/AnalysisAndPreparing
SoftProcessorUnit/Common
SoftProcessorUnit/Common/Stack
SoftProcessorUnit/SPU
SoftProcessorUnit/SPU/Core
SoftProcessorUnit/Syntax
SoftProcessorUnit/Syntax/Translation
SoftProcessorUnit/Syntax/Translation/MacroSyntax
SoftProcessorUnit/Syntax/Translation/Helpers
SoftProcessorUnit/WorkingDirectory
)


##
## SPU
##

add_executable( SPU
${SPU_SOURCES}
${SPU_PUBLIC_HEADERS}
${SPU_PROJECT_HEADERS}
${SPU_PRIVATE_HEADERS}
${SPU_RESOURCES}
)

target_include_directories(SPU PRIVATE
SoftProcessorUnit
)

target_link_libraries( SPU
${BEGIN_ALL_LOAD}
${SPU_STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${SPU_DEPENDENCIES}
${MULLE_SDE_LINKER_FLAGS}
)


##
## SPUAsm
##

add_executable( SPUAsm
${SPUASM_SOURCES}
${SPUASM_PUBLIC_HEADERS}
${SPUASM_PROJECT_HEADERS}
${SPUASM_PRIVATE_HEADERS}
${SPUASM_RESOURCES}
)

target_link_libraries( SPUAsm
${BEGIN_ALL_LOAD}
${SPUASM_STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${SPUASM_DEPENDENCIES}
${MULLE_SDE_LINKER_FLAGS}
)


##
## SPUDisAsm
##

add_executable( SPUDisAsm
${SPUDIS_ASM_SOURCES}
${SPUDIS_ASM_PUBLIC_HEADERS}
${SPUDIS_ASM_PROJECT_HEADERS}
${SPUDIS_ASM_PRIVATE_HEADERS}
${SPUDIS_ASM_RESOURCES}
)

target_link_libraries( SPUDisAsm
${BEGIN_ALL_LOAD}
${SPUDIS_ASM_STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${SPUDIS_ASM_DEPENDENCIES}
${MULLE_SDE_LINKER_FLAGS}
)

target_include_directories(SPUDisAsm PRIVATE
SoftProcessorUnit
)
