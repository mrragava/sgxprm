#include <stdio.h>
#include <string.h>

#include "openenclave/include/openenclave/enclave.h"
#include "openenclave/include/openenclave/internal/raise.h"
#include "openenclave/include/openenclave/internal/trace.h"
#include "openenclave/include/openenclave/corelibc/stdlib.h"

#include "sgxprm_t.h"

OE_SET_ENCLAVE_SGX(1,     /* ProductID */
                   1,     /* SecurityVersion */
                   true,  /* Debug */
                   25600, /* NumHeapPages */
                   2048,  /* NumStackPages */
                   1);    /* NumTCS */

void oe_ecall()
{
}
