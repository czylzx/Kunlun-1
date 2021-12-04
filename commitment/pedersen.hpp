#ifndef COMMITMENT_HPP_
#define COMMITMENT_HPP_

#include "../crypto/ec_point.hpp"
#include "../utility/routines.hpp"

namespace Pedersen{

// define PP of Com
struct PP
{
    ECPoint g; 
    std::vector<ECPoint> vec_h;  
    size_t N_max; 
};

/* Setup algorithm */ 
PP Setup(size_t N_max)
{ 
    PP pp;
    pp.N_max = N_max;
    pp.g = ECPoint(generator); 
    pp.vec_h = GenRandomECPointVector(N_max); 
    return pp; 
}


/* initialize the hashmap to accelerate decryption */
ECPoint Commit(PP &pp, std::vector<BigInt>& vec_m, BigInt r)
{
    if(pp.N_max < vec_m.size()){
        std::cerr << "message size is less than pp size" << std::endl;
    }
    size_t LEN = vec_m.size();
    std::vector<ECPoint> subvec_h(pp.vec_h.begin(), pp.vec_h.begin() + LEN);
    ECPoint commitment = pp.g * r + ECPointVectorMul(subvec_h, vec_m);
    return commitment;   
}


}
# endif




