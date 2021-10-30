#ifndef HEADER_PAGE_TABLE
#define HEADER_PAGE_TABLE

#include "Page.h"
#include <cstdlib>
#include <iostream>
#include <vector>

class PageTable
{
  public:
    PageTable(uint32_t, std::ostream* os);
    ~PageTable();
    Page* getPage(uint32_t addr);
    uint32_t getPageFrames();
    uint32_t getPageCount();
    uint32_t getWorkingSetSize();
    uint32_t getLastCyclesRun();
    uint32_t getMemAccesses();
    uint32_t getSwapIns();
    uint32_t getSwapOuts();
    uint32_t getPagesMalloced();
    Page** getPages();
    bool isPageMalloced();
  private:
    Page* swap(uint32_t addr);
    void createPage(uint32_t addr);
    uint32_t randy();
    void outputStatus();
    uint32_t pFCount;  // # of page frames
    uint32_t pCount;   // # of pages - total length of table
    Page** pages;
    uint32_t lastCyclesRun;
    bool pageMalloced;
    uint32_t memAccesses;
    uint32_t pagesMalloced;
    uint32_t swapIns;
    uint32_t swapOuts;
    std::ostream* os;
};

#endif //HEADER_PAGE_TABLE