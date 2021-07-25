///////////////////////////////////////////////////////////////////////////////
// Tyler Perkins
// 7-24-21
// Tyler's useful utilities for c++
//

namespace tylers_utilities{
    //constexpr hash function
    constexpr size_t hash(const char* str){
        const long long p = 131;
        const long long m = 4294967291; //2^32 - 5
        long long total = 0;
        long long current_multiplier = 1;
        for(int i = 0; str[i] != '\0'; ++i){
            total = (total + current_multiplier * str[i]) % m;
            current_multiplier = (current_multiplier * p) % m;
        }
        return total;
    }
}
