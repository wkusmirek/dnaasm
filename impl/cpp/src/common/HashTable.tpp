/**
 * \file HashTable.cpp
 * \brief the C++ file with implementation of hash table class
 *
 */

//#include "HashTable.hpp"

using namespace std;

namespace dnaasm {

    template<class Vertex>
    SparseHashTable<Vertex>::SparseHashTable(unsigned short K1)
        : K1_(K1)
        , hashTable_(K1, HashTableKeyHash(), HashTableKeyEqual()), dnaSequenceRepresentationConverter_(K1) 
    {}

    template<class Vertex>
    void SparseHashTable<Vertex>::clear() {
        return hashTable_.clear();
    }

    template<class Vertex>
    size_t SparseHashTable<Vertex>::size() const {
        return hashTable_.size();
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::begin() {
        return hashTable_.begin();
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::end() {
        return hashTable_.end();
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::find(const char* read) {
        return hashTable_.find(dnaSequenceRepresentationConverter_.convertToBitset(read));
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::find(bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer) {
        return hashTable_.find(bitsetK1Mer);
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::insert(const char* read, Vertex vertex) {
        return hashTable_.insert(SparseHashTable<Vertex>::value_type(dnaSequenceRepresentationConverter_.convertToBitset(read), vertex)).first;
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::iterator SparseHashTable<Vertex>::insert(bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, Vertex vertex) {
        return hashTable_.insert(SparseHashTable<Vertex>::value_type(bitsetK1Mer, vertex)).first;
    }

    template<class Vertex>
    bool SparseHashTable<Vertex>::isValid(const char* read, size_t size) {
        if (string(read, size).find_first_not_of("ACGT") == std::string::npos) {
            return true;
        } else {
            return false;
        }
    }

    template<class Vertex>
    typename SparseHashTable<Vertex>::HashTableType& SparseHashTable<Vertex>::getHashTable() {
        return hashTable_;
    }

}

