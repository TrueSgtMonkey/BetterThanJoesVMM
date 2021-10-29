#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

#define ADDRESS 960000

int parseString(std::string s);

int main(int argc, char* argv[])
{
    srand(time(0));
    std::ofstream ofs;
    int inpoots = 100;
    int p = 16;
    switch(argc)
    {
      case 1:
      {
        ofs.open("input.txt");
        break;
      }
      case 2:
      {
        ofs.open(argv[1]);
        break;
      }
      case 3:
      {
        ofs.open(argv[1]);
        inpoots = parseString(argv[2]);
        break;
      }
      case 4:
      {
        ofs.open(argv[1]);
        inpoots = parseString(argv[2]);
        p = parseString(argv[3]);
        break;
      }
    }

    ofs << "p " << (rand() % p + ((p > 4) ? p / 4 : 4)) << "\n";
    int inputs = rand() % inpoots + ((inpoots > 4) ? inpoots / 4 : 4);

    ofs << "w " << rand() % ADDRESS << " " << rand() % 9999 << "\n";
    int lastWrite = 0;
    for(int i = 1; i < inputs; i++)
    {
      int check = rand() % 2;
      if(check == 0)
      {
        lastWrite = rand() % ADDRESS;
        ofs << "w " << lastWrite << " " << rand() % 9999 << "\n";
        continue;
      }
      int useLastWrite = rand() % 2;
      if(useLastWrite == 0)
      {
        ofs << "r " << lastWrite << "\n";
        continue;
      }
      ofs << "r " << rand() % ADDRESS << "\n";
    }

    ofs.close();
    return 0;
}

int parseString(std::string s)
{
  int total = 0;
  for(int i = 0; i < s.size(); i++)
  {
    if(s[i] >= 48 && s[i] <= 57)
      total += (total * 10) + (s[i] - 48);
  }
  return total;
}
