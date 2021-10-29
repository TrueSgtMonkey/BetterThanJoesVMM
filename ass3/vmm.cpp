#include "vmm.h"

vmm::vmm(uint32_t pFCount, std::ostream* os)
{
    pd = new PageDirectory(pFCount, os);
    this->os = os;
    cycles = 0;
    accesses = 0;
    //*os << "os has been constructed in vmm\n";
}

vmm::~vmm()
{
    delete pd;
}

uint32_t vmm::read(uint32_t addr)
{
    parseAddr(addr);
    PageTable* pt = pd->getPageTable(ptAddr);
    uint32_t oldSwapIns = pt->getSwapIns();
    uint32_t oldSwapOuts = pt->getSwapOuts();
    Page* p = (pt)->getPage(pAddr);
    cycles += 3;
    cycles += pd->getLastCyclesRan() + pt->getLastCyclesRun() +
            p->getLastCyclesRun();
    uint32_t currAccesses = pd->getMemAccesses() + pt->getMemAccesses() +
                            p->getMemAccesses();
    accesses += currAccesses;
    if(oldSwapIns == pt->getSwapIns() && oldSwapOuts == pt->getSwapOuts())
        nonVMMCycles += currAccesses;
    printPdOnPageMalloc(pt);
    return p->read(byteOffset);
}

void vmm::write(uint32_t addr, uint32_t val)
{
    parseAddr(addr);
    PageTable* pt = pd->getPageTable(ptAddr);
    uint32_t oldSwapIns = pt->getSwapIns();
    uint32_t oldSwapOuts = pt->getSwapOuts();
    Page* p = (pt)->getPage(pAddr);
    p->write(byteOffset, val);
    cycles += 3;
    uint32_t currAccesses = pd->getMemAccesses() + pt->getMemAccesses() +
                            p->getMemAccesses();
    cycles += currAccesses;
    accesses += pd->getMemAccesses() + pt->getMemAccesses() +
                p->getMemAccesses();
    if(oldSwapIns == pt->getSwapIns() && oldSwapOuts == pt->getSwapOuts())
        nonVMMCycles += currAccesses;
    printPdOnPageMalloc(pt);
}

void vmm::printPdOnPageMalloc(PageTable* pt)
{
    if(pt->isPageMalloced())
    {
        *os << " * * * Done mallocing a new page Malloc User Page * * * " << std::endl;
        *os << "Dumping Page Directory:" << std::endl;
        std::vector<PageTable*> validTables =  pd->getValidTables();
        std::vector<uint32_t> validTableSpots = pd->getValidSpots();
        for(int i = 0; i < validTables.size(); i++)
        {
            *os << "pd[" << validTableSpots[i] << "].v   = " << validTables[i] << std::endl;
            *os << "pd[" << validTableSpots[i] << "].lru = " << validTableSpots[i] << std::endl;
        }
        *os << std::endl;

        *os << "Dumping Page Tables:" << std::endl;

        for(int i = 0; i < validTables.size(); i++)
        {
            *os << "Page Dir entry " << validTableSpots[i] << ":" << std::endl;
            Page** pages = validTables[i]->getPages();
            for(int j = 0; j < validTables[i]->getPageFrames(); j++)
            {
                if(pages[j] != nullptr)
                {
                    *os << "pt[" << j << "].v = " << pages[j];
                    *os << ", lru = " << j;
                    if(pages[j]->isModified())
                    {
                        *os << ", written";
                    }
                    *os << std::endl;
                }

            }
            *os << std::endl;
        }

    }
}

uint32_t* vmm::getMaxWorkingSetSize()
{
    return pd->getWorkingSetSize();
}

uint32_t vmm::getCycles()
{
    return cycles;
}

uint32_t vmm::getNonVMMCycles()
{
    return nonVMMCycles;
}

uint32_t vmm::getFrames()
{
    return pd->getFrames();
}

uint32_t vmm::getAccesses()
{
    return accesses;
}

uint32_t vmm::pdSwapIns()
{
    return pd->getTotalSwapIns();
}

uint32_t vmm::pdSwapOuts()
{
    return pd->getTotalSwapOuts();
}

uint32_t vmm::pdMallocedPages()
{
    return pd->getMallocedPages();
}

void vmm::parseAddr(uint32_t addr)
{
    //leftmost 10 bits
    ptAddr = (addr >> 22);

    //middle 10 bits
    //0x00 00 00 00
    //0000 0000 0011 1111 1111 1111 1111 1111
    //0000 0000 0000 0000 0000 0011 1111 1111
    pAddr = (addr >> 12) & 0x000003FF;

    //rightmost 12 bits
    byteOffset = addr & 0x00000FFF;


    /*
    std::cout << "ptAddr: " << ptAddr << "\n" << "pAddr: " << pAddr << "\n" <<
        "byteOffset: " << byteOffset << "\n";
    */
}

