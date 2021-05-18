cmake_minimum_required(VERSION 3.0.0)
project(sgxprm VERSION 1.0.0)

set(OPEN_ENCLAVE_SDK_SRC ${PROJECT_SOURCE_DIR}/external/openenclave)
add_subdirectory(src)
