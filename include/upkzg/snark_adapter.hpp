#pragma once
#include "types.hpp"

namespace upkzg {

// Minimal abstract SNARK adapter interface to plug in SIM-EXT SNARK
struct SNARKInterface {
    virtual ~SNARKInterface() = default;
    virtual void Keygen(...) = 0;
    virtual void Prove(...) = 0;
    virtual bool Verify(...) = 0;
};

}
