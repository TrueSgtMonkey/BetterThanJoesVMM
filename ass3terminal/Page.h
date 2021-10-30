#ifndef HEADER_PAGE
#define HEADER_PAGE

#include <stdint.h>
#include <iostream>

/**TODO: FIGURE OUT WHAT PAGE FRAMES ARE M8
*/
class Page
{
  public:
    Page(bool present, std::ostream* os);
    ~Page();
    int getSize();
    uint32_t read(uint32_t spot);
    void write(uint32_t spot, uint32_t val);
    bool isPresent();
    void setPresent(bool p);
    void setModified(bool);
    bool isModified();
    uint32_t getLastCyclesRun();
    uint32_t getMemAccesses();
    //void setSize(int size); //useless function for this project
  private:
    int sz;
    uint32_t* word;
    bool present;
    bool modified;
    uint32_t lastCyclesRun;
    uint32_t memAccesses;
    std::ostream* os;
};

#endif //HEADER_PAGE
