/**
 * \file OutputVCF.cpp
 * \brief the C++ file with implementation of class for generating output string in VCF format from set of mismatches
 *
 */

#include "OutputVCF.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    OutputVCF::OutputVCF(vector<Mismatch>& mismatches): mismatches_(mismatches), outputString_("") {}

    bool mismatchCmpLess(const Mismatch & m1, const Mismatch & m2) {
        if (m1.getOriginalRefIdx() != m2.getOriginalRefIdx())
            return m1.getOriginalRefIdx() < m2.getOriginalRefIdx();
        else if (m1.getReferenceMismatch() != m2.getReferenceMismatch())
            return m1.getReferenceMismatch() < m2.getReferenceMismatch();
        else if (m1.getSequenceMismatch() != m2.getSequenceMismatch())
            return m1.getSequenceMismatch() < m2.getSequenceMismatch();
        else
            return false;
    }

    bool mismatchCmpEqual(const Mismatch & m1, const Mismatch & m2) {
        return (m1.getOriginalRefIdx() == m2.getOriginalRefIdx() &&
                m1.getReferenceMismatch() == m2.getReferenceMismatch() &&
                m1.getSequenceMismatch() == m2.getSequenceMismatch());
    }

    string OutputVCF::generateVCFOutput() {
        sort(mismatches_.begin(), mismatches_.end(), mismatchCmpLess);
        mismatches_.erase(unique(mismatches_.begin(), mismatches_.end(), mismatchCmpEqual), mismatches_.end());
        outputString_ += "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n";

        for (auto it = mismatches_.begin(); it != mismatches_.end(); ++it) {
            if (string(it->getSequenceId()) == "") {
                outputString_ += (".\t" + to_string(it->getOriginalRefIdx())
                              + "\t.\t" + string(it->getReferenceMismatch())
                              + "\t" + string(it->getSequenceMismatch())+ "\t.\t.\t.\r\n");
            } else {
                outputString_ += (".\t" + to_string(it->getOriginalRefIdx())
                              + "\t" + string(it->getSequenceId())+ "\t" + string(it->getReferenceMismatch())
                              + "\t" + string(it->getSequenceMismatch())+ "\t.\t.\t.\r\n");
            }
        }
        return outputString_;
    }
}}

