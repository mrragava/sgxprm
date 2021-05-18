#include <ctime>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <linux/limits.h>
#include <memory>
#include <unistd.h>
#include <vector>
#include <assert.h>

#include "openenclave/include/openenclave/host.h"
#include "openenclave/include/openenclave/internal/error.h"

#include "sgxprm_u.h"

class sgxprm_enclave
{
  public:
    sgxprm_enclave()
    {
        std::vector<char> proc_path(PATH_MAX);
        assert(readlink("/proc/self/exe", proc_path.data(), PATH_MAX - 1) != -1);
        std::string proc_dir(proc_path.begin(), proc_path.end());
        std::string enc_path = proc_dir.substr(0, proc_dir.rfind("/"));        
        enc_path.append("/sgxprm_enc");
        assert(!access(enc_path.c_str(), F_OK));
        
        uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;
        oe_result_t result = oe_create_sgxprm_enclave(enc_path.c_str(), OE_ENCLAVE_TYPE_SGX, flags, NULL, 0, &enclave);
        if (result != OE_OK)
        {
            oe_put_err("Failed to create encalve, result=%u", result);
        }
    }

    ~sgxprm_enclave()
    {
        if (enclave)
        {
           oe_result_t result = oe_terminate_enclave(enclave);
            if (result != OE_OK)
                oe_put_err("Failed to terminate encalve, result=%u", result);
        }
    }

  protected:
    oe_result_t enclave_status = OE_OK;
    oe_enclave_t *enclave = nullptr;
};

int main()
{
    std::unique_ptr<sgxprm_enclave> prmenc;
    prmenc = std::make_unique<sgxprm_enclave>();

    return 0;
}
