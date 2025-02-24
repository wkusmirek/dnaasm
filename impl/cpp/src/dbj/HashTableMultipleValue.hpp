/**
 * \file HashTableMultipleValue.hpp
 * \brief the C++ file with declaration of hash table class (with multiple key values)
 *
 */

#ifndef HASH_TABLE_MULTIPLE_VALUE_HPP
#define HASH_TABLE_MULTIPLE_VALUE_HPP

#include <google/sparse_hash_map>

#include "globals.hpp"
#include "../common/HashTableKeyHash.hpp"
#include "../common/HashTableKeyEqual.hpp"
#include "../common/DnaSequenceRepresentationConverter.hpp"

namespace dnaasm { namespace dbj {

    class HashTableMultipleValue {

    public:
        typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

        typedef std::pair<DeBruijnGraphVertex, unsigned short> VertexOffsetType;

        typedef google::sparse_hash_map<std::bitset<2*MAX_KMER_LENGTH>,
                                        VertexOffsetType, HashTableKeyHash,
                                        HashTableKeyEqual> HashTableSingleValueType;

        typedef std::unordered_multimap<std::bitset<2*MAX_KMER_LENGTH>,
                                        VertexOffsetType,
                                        HashTableKeyHash,
                                        HashTableKeyEqual> HashTableMultipleValueType;

        CALC_DLL(explicit HashTableMultipleValue(unsigned short K1);)

        CALC_DLL(void clear();)

        CALC_DLL(size_t size() const;)

        CALC_DLL(std::vector<VertexOffsetType> find(const char* stringRepresentation);)

        CALC_DLL(std::vector<VertexOffsetType> find(std::bitset<2*MAX_KMER_LENGTH> bitsetRepresentation);)

        CALC_DLL(void insert(const char* read, DeBruijnGraphVertex vertex, unsigned short offset);)

        CALC_DLL(static bool isValid(const char* read, size_t size);)

        CALC_DLL(HashTableMultipleValueType& getHashTableMultiple();)

        CALC_DLL(HashTableSingleValueType& getHashTableSingle();)

    private:
        unsigned short K1_;
        HashTableSingleValueType hashTableSingle_;
        HashTableMultipleValueType hashTableMultiple_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        HashTableMultipleValue& operator=(const HashTableMultipleValue&)= delete;

    };

}}

#endif //HASH_TABLE_MULTIPLE_VALUE_HPP
