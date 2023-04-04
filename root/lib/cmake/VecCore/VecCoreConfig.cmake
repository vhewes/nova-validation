
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was VecCoreConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(VecCore_FOUND TRUE)

set(VecCore_VERSION 0.7.0)
set(VecCore_VERSION_MAJOR 0)
set(VecCore_VERSION_MINOR 7)
set(VecCore_VERSION_PATCH 0)

set_and_check(VecCore_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set_and_check(VecCore_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include")

set(VecCore_INCLUDE_DIRS "${VecCore_INCLUDE_DIR}")

list(APPEND CMAKE_MODULE_PATH "${VecCore_CMAKE_DIR}")

include(CMakeFindDependencyMacro)

if (VecCore_FIND_COMPONENTS MATCHES "CUDA")
  find_dependency(CUDA 7.5)
  if(CUDA_FOUND)
    set(VecCore_CUDA_FOUND True)
    set(VecCore_CUDA_DEFINITIONS -DVECCORE_ENABLE_CUDA)
    set(VecCore_CUDA_INCLUDE_DIR ${CUDA_INCLUDE_DIRS})
  endif()
endif()

if (VecCore_FIND_COMPONENTS MATCHES "UMESIMD")
  find_dependency(UMESIMD 0.8.1)
  if(UMESIMD_FOUND)
    set(VecCore_UMESIMD_FOUND True)
    set(VecCore_UMESIMD_DEFINITIONS -DVECCORE_ENABLE_UMESIMD)
    set(VecCore_UMESIMD_INCLUDE_DIR ${UMESIMD_INCLUDE_DIRS})
  endif()
endif()

if (VecCore_FIND_COMPONENTS MATCHES "Vc")
  find_dependency(Vc 1.3.3 CONFIG)
  if (Vc_FOUND)
    set(VecCore_Vc_FOUND True)
    set(VecCore_Vc_DEFINITIONS -DVECCORE_ENABLE_VC)
    set(VecCore_Vc_INCLUDE_DIR ${Vc_INCLUDE_DIR})
    set(VecCore_Vc_LIBRARIES ${VecCore_LIBRARIES} ${Vc_LIBRARIES})
  endif()
endif()

check_required_components(VecCore)

foreach(component ${VecCore_FIND_COMPONENTS})
  if("${component}" MATCHES "CUDA|UMESIMD|Vc")
    set(VecCore_DEFINITIONS ${VecCore_DEFINITIONS} ${VecCore_${component}_DEFINITIONS})
    set(VecCore_INCLUDE_DIRS ${VecCore_INCLUDE_DIRS} ${VecCore_${component}_INCLUDE_DIR})
    set(VecCore_LIBRARIES ${VecCore_LIBRARIES} ${VecCore_${component}_LIBRARIES})
  else()
    set(VecCore_FOUND False)
    set(_VecCore_NOT_FOUND_MESSAGE
      "Unknown component: ${component} (known components: CUDA, UMESIMD, Vc)")
    return()
  endif()
endforeach()

list(REMOVE_DUPLICATES VecCore_INCLUDE_DIRS)

if (VecCore_FOUND AND NOT TARGET VecCore::VecCore)
  add_library(VecCore::VecCore INTERFACE IMPORTED)
  set_target_properties(VecCore::VecCore PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${VecCore_INCLUDE_DIRS}")

  if (VecCore_DEFINITIONS)
    string(REGEX REPLACE "-D" "" _localdefs "${VecCore_DEFINITIONS}")
    set_target_properties(VecCore::VecCore PROPERTIES
      INTERFACE_COMPILE_DEFINITIONS "${_localdefs}")
    unset(_localdefs)
  endif()

  if (VecCore_LIBRARIES)
    set_target_properties(VecCore::VecCore PROPERTIES
      INTERFACE_LINK_LIBRARIES "${VecCore_LIBRARIES}")
  endif()
endif()
