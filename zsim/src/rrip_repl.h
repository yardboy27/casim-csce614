#ifndef RRIP_REPL_H_
#define RRIP_REPL_H_

#include "repl_policies.h"

// Static RRIP
class SRRIPReplPolicy : public ReplPolicy {
    protected:
        // add class member variables here
        uint8_t maxRPV;
        uint8_t* array;
        uint32_t numLines;

    public:
        // add member methods here, refer to repl_policies.h
        explicit SRRIPReplPolicy(uint8_t _maxRPV, uint32_t _numLines) : maxRPV(_maxRPV), numLines(_numLines) {
            array = gm_calloc<uint8_t>(numLines);

            // initialize all invalid entries to max rpv
            for (uint32_t i = 0; i < numLines; ++i) {
                array[i] = maxRPV;
            }
        }

        ~SRRIPReplPolicy() {
            gm_free(array);
        }

        void increment_all() { // increment the RRPV for all the array items by 1
            // TODO 
            for (uint32_t i = 0; i < numLines; ++i)
            {
                if (array[i] < maxRPV)
                    ++array[i];
            }
        }

        void update(uint32_t id, const MemReq* req) { // sets the RRPV value to zero on cache hit
            array[id] = 0;
        }

        template <typename C> inline uint32_t rank(const MemReq* req, C cands) {
            uint32_t bestCand = -1;
            uint8_t bestScore = 0;
            for (auto ci = cands.begin(); ci != cands.end(); ci.inc()) {
                uint8_t s = score(*ci);

                if (s >= bestScore) {
                    bestCand = *ci;
                    bestScore = s;
                }

                if (bestScore == this->maxRPV)
                    return bestCand;
            }

            // if bestScore < maxRPV, increment all the RPV values
            increment_all()
            return rank(req, cands);
        }

        // DECL_RANK_BINDINGS;

    private:
        inline uint8_t score(uint32_t id) {
            return ( array[id] )
        }
};
#endif // RRIP_REPL_H_
