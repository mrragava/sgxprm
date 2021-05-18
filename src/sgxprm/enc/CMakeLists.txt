set(EDL_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../sgxprm.edl)
add_custom_command(
  OUTPUT sgxprm_t.h sgxprm_t.c sgxprm_args.h
  DEPENDS ${EDL_FILE}
  COMMAND
    openenclave::oeedger8r --trusted ${EDL_FILE}
    --search-path ${OE_INCLUDEDIR} 
    --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx)

add_executable(sgxprm_enc
  enc.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/sgxprm_t.c)

target_compile_definitions(sgxprm_enc PUBLIC OE_API_VERSION=2)

target_include_directories(sgxprm_enc
  PRIVATE 
  ${PROJECT_SOURCE_DIR}/external
  ${PROJECT_SOURCE_DIR}/external/openenclave/
  ${PROJECT_SOURCE_DIR}/external/openenclave/include
 ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(sgxprm_enc 
  PRIVATE 
  openenclave::oeenclave
  openenclave::oelibcxx
  openenclave::oelibc
  openenclave::oecore
  openenclave::oecryptombedtls)
