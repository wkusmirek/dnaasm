#ifndef ASSOCIATION_H_
#define ASSOCIATION_H_

namespace dnaasm { namespace bst {

    /*
        start0    - read0's first matching index
        start1    - read1's first matching index
        end0      - read0's last matching index
        end1      - read1's last matching index

        CCCACGT     -read 0
           ACGTAAA  -read 1
        0123456789
        ====> Association(3, 0, 6, 3 )
    */
    struct Association
    {
        Association(unsigned s0, unsigned s1,
                    unsigned e0, unsigned e1,
                    float sc = 0.0f)
            :start0_(s0), start1_(s1),
             end0_(e0), end1_(e1),
             score_(sc)
        {}
        Association() {}
        unsigned start0_, start1_;
        unsigned end0_, end1_;
        float score_;
    };

    using As = Association;
}}

#endif
