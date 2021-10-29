#include "Page.h"

Page::Page(bool present, std::ostream* os)
{
    sz = 4096;
    word = new uint32_t[sz];
    this->present = present;
    modified = false;
    lastCyclesRun = 0;
    memAccesses = 0;
    this->os = os;
}

Page::~Page()
{
    delete[] word;
}

int Page::getSize()
{
    return sz;
}

uint32_t Page::getLastCyclesRun()
{
    uint32_t last = lastCyclesRun;
    lastCyclesRun = 0;
    return last;
}

uint32_t Page::getMemAccesses()
{
    uint32_t mem = memAccesses;
    memAccesses = 0;
    return mem;
}

uint32_t Page::read(uint32_t spot)
{
    memAccesses++;
    lastCyclesRun++;
    return (present && spot < sz - 1) ? word[spot] : 0;
}

void Page::write(uint32_t spot, uint32_t val)
{
    memAccesses++;
    lastCyclesRun++;
    modified = true;
    word[spot] = val;
}

void Page::setModified(bool modified)
{
   this->modified = modified;
}

bool Page::isModified()
{
    return modified;
}

bool Page::isPresent()
{
    return present;
}

void Page::setPresent(bool p)
{
    present = p;
}

/*
void Page::setSize(int size)
{
  uint32_t* temp = new uint32_t[size];
  for(int i = 0; i < sz; i++)
  {
    temp[i] = word[i];
  }
  delete[] word;
  word = temp;
  sz = size;
}
*/

