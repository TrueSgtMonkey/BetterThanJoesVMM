#include <iostream>
#include "Page.h"
#include "PageTable.h"
#include "PageDirectory.h"
#include "vmm.h"
#include <cstdlib>
#include <time.h>
#include <fstream>

void test();
void pageStats(vmm* machine, std::ostream&);
uint32_t parseString(std::string s);

int main(int argc, char* argv[])
{
    std::ifstream ifs;
    std::ofstream ofs;
    bool fileoutput = false;

    srand(time(0));
    if(argc == 2)
    {
        ifs.open(argv[1]);
    }
    else if(argc == 3)
    {
        ifs.open(argv[1]);
        ofs.open(argv[2]);
        fileoutput = true;
    }
    else
    {
        ifs.open("input.txt");
    }

    std::string input;
    ifs >> input;
    uint32_t frames;
    if(input == "p")
    {
        ifs >> input;
        frames = parseString(input);
    }
    else
    {
        std::cout << "cannot determine page!\n" << "Place p at beginning of "
            << "file.\n";
        return -1;
    }

    vmm machine(frames, (fileoutput) ? &ofs : &std::cout);

    uint32_t line = 2;
    while(ifs >> input)
    {
        if(input == "r")
        {
            ifs >> input;
            uint32_t address = parseString(input);
            std::cout << "read: " << machine.read(address) << " at " << address
                 << "\n";
        }
        else if(input == "w")
        {
            ifs >> input;
            uint32_t address = parseString(input);
            ifs >> input;
            uint32_t val = parseString(input);
            machine.write(address, val);

            std::cout << "write: " << val << " at " << address << "\n";
        }
        else
        {
            std::cout << "error, bad input on line: " << line;
            break;
        }
        line++;
    }

    pageStats(&machine, ofs);

    ifs.close();
    ofs.close();
    return 0;
}

uint32_t parseString(std::string s)
{
    uint32_t sum = 0;
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] >= 48 && s[i] <= 57)
            sum = (sum * 10) + (s[i] - 48);
    }
    return sum;
}

void test()
{
    std::ofstream ofs;
    ofs.open("input.txt");

    ofs << "p 9\n";

    srand((unsigned)time(nullptr));
    vmm machine(9, &ofs);

    ofs << "w " << 0 << " 24\n";
    ofs << "w " << 0x1000 << " 2\n";
    ofs << "w " << 0x2000 << " 4\n";
    ofs << "w " << 0x3000 << " 21\n";
    machine.write(0x00000000, 24);
    machine.write(0x00001000, 2);
    machine.write(0x00002000, 4);
    machine.write(0x00003000, 21);

    for(uint32_t i = 0; i < 80; i++)
    {
        uint32_t thrash1 = i << rand() % 16;
        uint32_t thrash2 = i << rand() % 16;
        machine.write(thrash1, i);
        ofs << "w " << thrash1 << " " << i << "\n";
        std::cout << machine.read(thrash2) << std::endl;
        ofs << "r " << thrash2 << "\n";
    }

    pageStats(&machine, std::cout);
    pageStats(&machine, ofs);

    ofs.close();
}

void pageStats(vmm* machine, std::ostream& os)
{
    os << "* * * Paging Activity Statistics * * *\n";
    os << "number of memory accesses       = " << machine->getAccesses()
        << "\n";
    os << "number of triples               = " << machine->getAccesses()
        + 1 << "\n";
    os << "number of swap-ins (faults)     = " << machine->pdSwapIns()
        << "\n";
    os << "number of swap-outs             = " << machine->pdSwapOuts()
        << "\n";
    os << "total number of pages malloced  = " << machine->pdMallocedPages()
        << "\n";
    os << "number of pages for Page Tables = 1\n";
    os << "number of page frames for user  = " << machine->getFrames()
        << "\n";
    os << "total memory cycles             = " << machine->getCycles()
        << "\n";
    os << "cycles w/o Vmm                  = " << machine->getAccesses() * 10
        << "\n";
    os << "cycles per swap_in              = 5000\n";
    os << "cycles per swap_out             = 5000\n";

    //make sure to delete as it returns a heap array
    uint32_t* sets = machine->getMaxWorkingSetSize();
    os << "last working set size           = " << sets[0] << "\n";
    os << "max working set size ever       = " << sets[1] << "\n";
    os << "max physical pages              = " << sets[2] << "\n";
    delete[] sets;

    os << "page size                       = 4096\n";
    os << "replacement algorithm           = random\n";
    os << "Address range                   = " << " . . . \n";
}


/*
int main()
{
    PageDirectory pd;

    pd.createTable(0, 9);
    uint32_t addr = 5;

    std::cout << pd.getPageTable(0)->getPageCount() << std::endl;
    for(int i = 0; i < 9; i++)
    {
        pd.getPageTable(0)->createPage();
        pd.getPageTable(0)->swap();
        std::cout << "addr: " << pd.getPageTable(0)->getAddr() << std::endl;
    }

    return 0;
}
 */
