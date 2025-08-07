// c_cpp_hash_tables_benchmark/blueprints/uint64_struct448_murmur/blueprint.h
// Copyright (c) 2024 Jackson L. Allan.
// Distributed under the MIT License (see the accompanying LICENSE file).

// #include <numeric>
#include <random>
#include <unordered_set>
#include <vector>

#include <cassert>
#include <cstdint>

#define UINT64_STRUCT448_MURMUR_ENABLED

struct uint64_struct448_murmur
{
  using key_type = uint64_t;
  using value_type = struct ABC {
      uint64_t dummy[ 7 ];
    };

  static constexpr const char *label = "64-bit integer key, 448-bit value";
  
  // MurmurHash3’s 64-bit finalizer.
  static uint64_t hash_key( const key_type &key )
  {
    uint64_t result = key;
    result ^= result >> 33;
    result *= 0xff51afd7ed558ccdull;
    result ^= result >> 33;
    result *= 0xc4ceb9fe1a85ec53ull;
    result ^= result >> 33;
    return result;
  }

  static bool cmpr_keys( const key_type &key_1, const key_type &key_2 )
  {
    return key_1 == key_2;
  }

  static void fill_unique_keys( std::vector<key_type> &keys )
  {
    // sequence keys
    // std::iota( keys.begin(), keys.end(), 0 );
    
    // random keys
    std::mt19937 mt(0);
    std::uniform_int_distribution<int> dist(0, INT_MAX/2);
    std::unordered_set<key_type> set;
    while (set.size() != keys.size())
      set.insert(dist(mt));
    
    auto it = set.begin();
    for (auto& k : keys)
      k = *it++;
    assert(it == set.end());
  }
};
