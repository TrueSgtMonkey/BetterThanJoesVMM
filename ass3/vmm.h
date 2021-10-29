#ifndef HEADER_VMM
#define HEADER_VMM

#include "PageDirectory.h"
#include <iostream>

class vmm
{
    public:
        vmm(uint32_t pFCount, std::ostream* os);
        ~vmm();
        uint32_t read(uint32_t addr);
        void write(uint32_t addr, uint32_t val);
        uint32_t getCycles();
        uint32_t getNonVMMCycles();
        uint32_t* getMaxWorkingSetSize();
        uint32_t getFrames();
        uint32_t getAccesses();
        uint32_t pdSwapIns();
        uint32_t pdSwapOuts();
        uint32_t pdMallocedPages();
    private:
        void parseAddr(uint32_t addr);
        void printPdOnPageMalloc(PageTable* pt);
        PageDirectory* pd;
        uint32_t ptAddr;
        uint32_t pAddr;
        uint32_t byteOffset;
        uint32_t cycles;
        uint32_t nonVMMCycles;
        uint32_t accesses;
        std::ostream* os;
};

#endif //HEADER_VMM