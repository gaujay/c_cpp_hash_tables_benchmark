// c_cpp_hash_tables_benchmark/blueprints/stdstring_uint64_fnv1a/blueprint.h
// Copyright (c) 2024 Jackson L. Allan.
// Distributed under the MIT License (see the accompanying LICENSE file).

#include <string>
#include <vector>

#include <cstdint>
#include <cstring>

#define STDSTRING_UINT64_FNV1A_ENABLED

struct stdstring_uint64_fnv1a
{
  using key_type = std::string;
  using value_type = uint64_t;
  static constexpr const char *label = "32-char std-string key, 64-bit value";

  static constexpr size_t string_length = 32;
  
  // FNV-1a.
  static uint64_t hash_key( const key_type &key )
  {
    size_t hash = 0xcbf29ce484222325ull;
    for (char c : key)
      hash = ( (unsigned char)c ^ hash ) * 0x100000001b3ull;

    return hash;
  }

  static bool cmpr_keys( const key_type &key_1, const key_type &key_2 )
  {
    return key_1 == key_2;
  }

  // Fills the keys array.
  static void fill_unique_keys( std::vector<key_type> &keys )
  {
    char current[ string_length ];
    memset( current, 'a', string_length );

    for( size_t i = 0; i < keys.size(); ++i )
    {
      auto& key = keys[ i ];
      key.assign(current, string_length);

      for( size_t j = 0; j < string_length; ++j )
      {
        if( ++current[ j ] <= 'z' )
          break;

        current[ j ] = 'a';
      }
    }
  }
};
