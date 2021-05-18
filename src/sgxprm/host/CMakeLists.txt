
set(EDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../sgxprm.edl)

add_custom_command(
  OUTPUT sgxprm_u.h sgxprm_u.c
  DEPENDS ${EDL_FILE}
  COMMAND
    openenclave::oeedger8r --untrusted ${EDL_FILE}
    --search-path ${OE_INCLUDEDIR} 
    --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx)

add_executable(sgxprm_host
  host.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/sgxprm_u.c)

target_include_directories(sgxprm_host
  PRIVATE
  ${PROJECT_SOURCE_DIR}/external
  ${PROJECT_SOURCE_DIR}/external/openenclave/
  ${PROJECT_SOURCE_DIR}/external/openenclave/include
  ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(sgxprm_host 
  PRIVATE 
  openenclave::oehost)
