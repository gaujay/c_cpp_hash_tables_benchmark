// c_cpp_hash_tables_benchmark/shims/boost_unordered_flat_map/shim.h
// Copyright (c) 2024 Jackson L. Allan.
// Distributed under the MIT License (see the accompanying LICENSE file).

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Woverflow"
// #include "absl/container/internal/raw_hash_set.cc"
// #include "absl/base/internal/raw_logging.cc"
// #include "absl/hash/internal/hash.cc"
// #include "absl/hash/internal/city.cc"
// #include "absl/hash/internal/low_level_hash.cc"
// #include "absl/container/flat_hash_map.h"
#include "folly/container/F14Map.h"
#pragma GCC diagnostic pop

#include <cstddef>

template< typename blueprint > struct folly_f14_value_map
{
  struct hash
  {
    using is_avalanching = void;

    std::size_t operator()( const blueprint::key_type &key ) const
    {
      return blueprint::hash_key( key );
    }
  };

  struct cmpr
  {
    bool operator()( const blueprint::key_type &key_1, const blueprint::key_type &key_2 ) const
    {
      return blueprint::cmpr_keys( key_1, key_2 );
    }
  };

  using table_type = folly::F14ValueMap<
    typename blueprint::key_type,
    typename blueprint::value_type,
    hash,
    // folly::f14::DefaultHasher<typename blueprint::key_type>,
    cmpr
  >;

  static table_type create_table()
  {
    table_type table;
    table.max_load_factor( MAX_LOAD_FACTOR );
    return table;
  }

  static table_type::iterator find( table_type &table, const blueprint::key_type &key )
  {
    return table.find( key );
  }

  static void insert( table_type &table, const blueprint::key_type &key )
  {
    table[ key ] = typename blueprint::value_type();
  }

  static void erase( table_type &table, const blueprint::key_type &key )
  {
    table.erase( key );
  }
  
  static void eraseN( table_type &table, std::size_t n )
  {
    auto it = table.begin();
    for (std::size_t i = 0u; i < n; ++i)
      it = table.erase(it);
  }

  static table_type::iterator begin_itr( table_type &table )
  {
    return table.begin();
  }

  static bool is_itr_valid( table_type &table, table_type::iterator &itr )
  {
    return itr != table.end();
  }

  static void increment_itr( table_type &, table_type::iterator &itr )
  {
    ++itr;
  }

  static const blueprint::key_type &get_key_from_itr( table_type &, table_type::iterator &itr )
  {
    return itr->first;
  }

  static const blueprint::value_type &get_value_from_itr( table_type &, table_type::iterator &itr )
  {
    return itr->second;
  }

  static void destroy_table( table_type & )
  {
    // RAII handles destruction.
  }
};

template<> struct folly_f14_value_map< void >
{
  static constexpr const char *label = "folly";
  static constexpr const char *color = "rgb( 61, 79, 210 )";
  static constexpr bool tombstone_like_mechanism = false;
};
