#include <fstream>
#include <iostream>
#include "Parser/Parser.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Missing argument\n";
    return 1;
  }

  try
  {
    std::ifstream in(argv[1]);

    if (!in)
    {
      std::cerr << "Could not open file\n";
      return 1;
    }

    Parser parser(in);

    in.close();
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
