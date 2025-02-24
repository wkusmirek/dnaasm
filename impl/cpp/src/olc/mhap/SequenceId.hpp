#ifndef SEQUENCEID_HPP
#define SEQUENCEID_HPP

#include <cstdint>
#include <string>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            class SequenceId {
            public:
                SequenceId(int64_t id, bool isFwd) : id_(id), isFwd_(isFwd) {}
                SequenceId(int64_t id) : SequenceId(id, true) {}
                SequenceId() : SequenceId(0, false) {}

                SequenceId complimentId() { return SequenceId(id_, !isFwd_); }

                const bool operator==(const SequenceId &rhs) const {
                    return (id_ == rhs.id_) && (isFwd_ == rhs.isFwd_);
                }

                int64_t getHeaderId() const {
                    return id_;
                }

                const bool isForward() const { return isFwd_; }
                int32_t hash() const { return isFwd_ ? static_cast<int32_t>(id_) : -static_cast<int32_t>(id_); }
                std::string getHeader() const { return std::to_string(id_); }

            private:
                int64_t id_;
                bool isFwd_;
            };

            struct SequenceIdHash {
                std::size_t operator()(const SequenceId& sId) const {
                    return static_cast<std::size_t>(sId.hash());
                }
            };
        }
    }
}

#endif //SEQUENCEID_HPP