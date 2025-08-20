#pragma once
#include "types.hpp"

namespace upkzg {

// Note: KGen should be test-only (in production initial SRS is not fully trusted)
SRS KGen(uint32_t max_degree, std::function<Fr()> rng);

// Serialize / deserialize SRS
std::string SRS_serialize(const SRS &srs);
SRS SRS_deserialize(const std::string &data);

}
