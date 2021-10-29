#include "PageDirectory.h"

PageDirectory::PageDirectory(uint32_t pFCount, std::ostream* os)
{
    frames = pFCount;
    pTCount = 1024;
    pageTables = new PageTable* [pTCount];
    lastCyclesRan = 0;
    memAccesses = 0;
    this->os = os;
}

PageDirectory::~PageDirectory()
{
    delete[] pageTables;
}

PageTable* PageDirectory::getPageTable(uint32_t spot)
{
    lastCyclesRan++;
    createTable(spot);
    memAccesses++;
    lastTable = pageTables[spot];
    return pageTables[spot];
}

std::vector<uint32_t> PageDirectory::getValidSpots()
{
    return createdSpots;
}

std::vector<PageTable*> PageDirectory::getValidTables()
{
    std::vector<PageTable*> valid;
    for(int i = 0; i < createdSpots.size(); i++)
    {
        valid.push_back(pageTables[createdSpots[i]]);
    }
    return valid;
}

void PageDirectory::createTable(uint32_t spot)
{
    //only creates a table if we have not made one yet
    if(binarySearch(createdSpots, 0, createdSpots.size(), spot) == -1)
    {
        lastCyclesRan++;
        std::cout << "making new table!\n";
        pageTables[spot] = new PageTable(frames, os);

        memAccesses++;
        createdSpots.push_back(spot);
        std::sort(createdSpots.begin(), createdSpots.end());

        //printing page directory status
        *os << " * * * Done mallocing a new Page Table * * *\n";
        *os << "Dumping Page Directory:\n";
        for(int i = 0; i < createdSpots.size(); i++)
        {
            *os << "pd[" << createdSpots[i] << "].v   = " << pageTables[createdSpots[i]] << std::endl;
            *os << "pd[" << createdSpots[i] << "].lru = " << createdSpots[i] << std::endl;
        }

        *os << std::endl << "Dumping Page Tables:" << std::endl;
        for(int i = 0; i < createdSpots.size(); i++)
        {
            *os << "Page Dir Entry: " << createdSpots[i] << std::endl;
        }
        *os << std::endl;
    }
}

uint32_t PageDirectory::getLastCyclesRan()
{
    uint32_t last = lastCyclesRan;
    lastCyclesRan = 0;
    return last;
}

uint32_t PageDirectory::getMemAccesses()
{
    uint32_t mem = memAccesses;
    memAccesses = 0;
    return mem;
}

uint32_t PageDirectory::getTotalSwapIns()
{
    uint32_t total = 0;
    for(int i = 0; i < createdSpots.size(); i++)
    {
        total += pageTables[createdSpots[i]]->getSwapIns();
    }
    return total;
}

uint32_t PageDirectory::getTotalSwapOuts()
{
    uint32_t total = 0;
    for(int i = 0; i < createdSpots.size(); i++)
    {
        total += pageTables[createdSpots[i]]->getSwapOuts();
    }
    return total;
}

uint32_t PageDirectory::getMallocedPages()
{
    uint32_t total = 0;
    for(int i = 0; i < createdSpots.size(); i++)
    {
        total += pageTables[createdSpots[i]]->getPagesMalloced();
    }
    return total;
}

uint32_t PageDirectory::getPageTableCount()
{
    return pTCount;
}

uint32_t* PageDirectory::getWorkingSetSize()
{
    uint32_t* workingSets = new uint32_t[3];
    workingSets[1] = 0;
    for(int i = 0; i < createdSpots.size(); i++)
    {
        uint32_t curr = pageTables[createdSpots[i]]->getWorkingSetSize();
        if(workingSets[1] < curr)
        {
            workingSets[1] = curr;
            workingSets[2] = curr;
        }
    }
    workingSets[0] = lastTable->getWorkingSetSize();
    return workingSets;
}

int PageDirectory::binarySearch(std::vector<uint32_t> arr, int l, int r, uint32_t x)
{
    if(arr.size() == 1)
    {
        return 0;
    }
    if(arr.size() > 1)
    {
        while (l <= r)
        {
            int m = l + (r - l) / 2;
            if (arr[m] == x)
                return m;
            if (arr[m] < x)
                l = m + 1;
            else
                r = m - 1;
        }
    }

    return -1;
}

uint32_t PageDirectory::getFrames()
{
    return frames;
}
