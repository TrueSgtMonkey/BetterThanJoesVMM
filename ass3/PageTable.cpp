#include "PageTable.h"

/* Total length of table is fixed to 1024 for this assignment
Page frames are allocated from input though
pCount will only utilize the leftmost bits for accessing */
PageTable::PageTable(uint32_t frames, std::ostream* os)
{
    if (frames > 1024)
    {
        pFCount = 1024;
    }
    else
    {
        pFCount = frames;
    }

    pCount = 1024;
    pageMalloced = false;
    pages = new Page* [pCount];
    lastCyclesRun = 0;
    memAccesses = 0;
    swapIns = 0;
    swapOuts = 0;
    pagesMalloced = 0;

    this->os = os;

    outputStatus();
}

void PageTable::outputStatus()
{

}

PageTable::~PageTable()
{
    delete [] pages;
}

Page** PageTable::getPages()
{
    return pages;
}

Page* PageTable::swap(uint32_t addr)
{
    //selecting victim page (10 cycles)
    uint32_t frame = randy() % pFCount;
    lastCyclesRun += 11;

    //overwrite that spot!
    memAccesses += 2;
    if(pages[frame] == nullptr || !(pages[frame]->isModified()))
    {
        lastCyclesRun += 3;
        pages[frame] = pages[addr];
        pages[addr] = nullptr;
        pages[frame]->setPresent(true);
        pages[frame]->setModified(false);
        return pages[frame];
    }

    lastCyclesRun += 5001;

    swapOuts++;
    //swapping (5000 cycles)
    Page* temp = pages[addr];
    pages[addr] = pages[frame];
    pages[frame] = temp;
    pages[addr]->setPresent(false);
    pages[frame]->setPresent(true);
    memAccesses += 7;
    std::cout << "swap performed\n";

    return pages[frame];
}

uint32_t PageTable::getWorkingSetSize()
{
    uint32_t total = 0;
    for(int i = 0; i < pFCount; i++)
    {
        if(pages[i] != nullptr)
            total++;
    }
    return total;
}

Page* PageTable::getPage(uint32_t addr)
{
    pageMalloced = false;
    lastCyclesRun++;
    std::cout << "addr: " << addr << "\n";
    memAccesses++;
    if(addr >= pFCount && pages[addr] != nullptr)
    {
        swapIns++;
        lastCyclesRun += 5000;
    }
    //page has been malloced
    if(pages[addr] == nullptr)
    {
        pageMalloced = true;
        std::cout << "making new page!\n";
        lastCyclesRun++;
        createPage(addr);
    }
    //this page is not in memory, so we need to access virtual memory
    if(addr >= pFCount)
    {
        std::cout << "going into swap function\n";
        Page* p = swap(addr);
        memAccesses++;
        if(pages[addr] == nullptr)
        {
            //we did not swap
        }
        return p;
    }

    lastCyclesRun += 10;
    memAccesses++;
    return pages[addr];
}

bool PageTable::isPageMalloced()
{
    return pageMalloced;
}

//bottm gear
//love you cutie
void PageTable::createPage(uint32_t addr)
{
    if(addr < pFCount)
        pages[addr] = new Page(true, os);
    else
        pages[addr] = new Page(false, os);

    memAccesses++;
    pagesMalloced++;
}

uint32_t PageTable::getPageFrames()
{
  return pFCount;
}

uint32_t PageTable::getPageCount()
{
  return pCount;
}

uint32_t PageTable::getLastCyclesRun()
{
    uint32_t last = lastCyclesRun;
    lastCyclesRun = 0;
    return last;
}

uint32_t PageTable::getMemAccesses()
{
    uint32_t mem = memAccesses;
    memAccesses = 0;
    return mem;
}

uint32_t PageTable::getSwapIns()
{
    return swapIns;
}

uint32_t PageTable::getSwapOuts()
{
    return swapOuts;
}

uint32_t PageTable::getPagesMalloced()
{
    return pagesMalloced;
}

uint32_t PageTable::randy()
{
  return (rand() << 17) | (rand() << 2) | (rand() >> 13);
}