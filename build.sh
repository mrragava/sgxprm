#!/bin/bash

export SGX_PRM_ROOT=${PWD}
export SGX_PRM_BUILD=${PWD}/build
export SGXPRM_TOOL_BUILD=${SGX_PRM_BUILD}/sgxprm_build
export OE_SRC_ROOT=${PWD}/external/openenclave

export OE_BUILD=${SGX_PRM_BUILD}/oe_build
export OE_INSTALL_PREFIX=${SGX_PRM_BUILD}/oe_install_prefix

CLEAN=0
for i in "$@"
do
case $i in
    -c|--clean)
    CLEAN=1
    ;;
esac
done

if [[ ${CLEAN} -ne 0 ]]; then
        rm -rf "$SGX_PRM_BUILD"
        mkdir -p "$SGX_PRM_BUILD"

        mkdir -p "$OE_BUILD"
        mkdir -p "$OE_INSTALL_PREFIX"
        pushd "$OE_BUILD"
        cmake "$OE_SRC_ROOT" -GNinja \
                -DBUILD_TESTS=OFF \
                -DCMAKE_C_COMPILER="clang-8" \
                -DCMAKE_CXX_COMPILER="clang++-8" \
                -DCMAKE_BUILD_TYPE=Debug \
                -DCMAKE_C_FLAGS_DEBUG="-O0 -g" \
                -DCMAKE_CXX_FLAGS_DEBUG="-O0 -g" \
                -DCMAKE_INSTALL_PREFIX="$OE_INSTALL_PREFIX"
        ninja install -j6
        popd
fi

rm -rf "$SGXPRM_TOOL_BUILD"
mkdir -p "$SGXPRM_TOOL_BUILD"
pushd "$SGXPRM_TOOL_BUILD"
cmake "$SGX_PRM_ROOT" -GNinja \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_C_FLAGS_DEBUG="-O0 -g" \
        -DCMAKE_CXX_FLAGS_DEBUG="-O0 -g" \
        -DCMAKE_C_COMPILER="clang-8" \
        -DCMAKE_CXX_COMPILER="clang++-8" \
        -DCMAKE_PREFIX_PATH="$OE_INSTALL_PREFIX"
ninja -j6
popd