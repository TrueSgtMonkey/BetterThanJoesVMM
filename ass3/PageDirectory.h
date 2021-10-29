#ifndef HEADER_PAGE_DIRECTORY
#define HEADER_PAGE_DIRECTORY

#include "PageTable.h"
#include <vector>

class PageDirectory
{
  public:
    PageDirectory(uint32_t, std::ostream* os);
    ~PageDirectory();
    uint32_t getPageTableCount();
    uint32_t* getWorkingSetSize();
    PageTable* getPageTable(uint32_t spot);
    std::vector<uint32_t> getValidSpots();
    std::vector<PageTable*> getValidTables();
    uint32_t getFrames();
    uint32_t getLastCyclesRan();
    uint32_t getMemAccesses();
    uint32_t getMallocedPages();
    uint32_t getTotalSwapIns();
    uint32_t getTotalSwapOuts();
  private:
    void createTable(uint32_t);
    int binarySearch(std::vector<uint32_t> arr, int l, int r, uint32_t x);
    uint32_t pTCount;
    std::vector<uint32_t> createdSpots;
    uint32_t frames;
    uint32_t lastCyclesRan;
    PageTable** pageTables;
    PageTable* lastTable;
    uint32_t memAccesses;
    std::ostream* os;
};

#endif //HEADER_PAGE_DIRECTORY