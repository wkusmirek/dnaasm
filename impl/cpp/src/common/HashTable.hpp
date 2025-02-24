/**
 * \file HashTable.hpp
 * \brief the C++ file with declaration of hash table class
 *
 */

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <google/sparse_hash_map>

#include "HashTableKeyHash.hpp"
#include "HashTableKeyEqual.hpp"
#include "DnaSequenceRepresentationConverter.hpp"

namespace dnaasm {

    template<class Vertex>
    class SparseHashTable {

    public:
        //typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor Vertex;

        typedef google::sparse_hash_map<std::bitset<2*MAX_KMER_LENGTH>,
                                        Vertex,
                                        HashTableKeyHash,
                                        HashTableKeyEqual> HashTableType;
        typedef typename HashTableType::iterator iterator;
        typedef typename HashTableType::value_type value_type;

        CALC_DLL(SparseHashTable();)

        CALC_DLL(explicit SparseHashTable(unsigned short K1);)

        CALC_DLL(void clear();)

        CALC_DLL(size_t size() const;)

        CALC_DLL(iterator begin();)

        CALC_DLL(iterator end();)

        CALC_DLL(iterator find(const char* stringRepresentation);)

        CALC_DLL(iterator find(std::bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer);)

        CALC_DLL(iterator insert(const char* read, Vertex vertex);)

        CALC_DLL(iterator insert(std::bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, Vertex vertex);)

        CALC_DLL(static bool isValid(const char* read, size_t size);)

        CALC_DLL(HashTableType& getHashTable();)

    private:
        unsigned short K1_;
        HashTableType hashTable_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        SparseHashTable& operator=(const SparseHashTable&)= delete;

    };
}

/** Include .cpp file with definition of template **/
#include "HashTable.tpp"

#endif //HASH_TABLE_HPP
