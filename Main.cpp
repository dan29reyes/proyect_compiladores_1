#include <fstream> 
#include <iostream>
#include "Lexer/Lexer.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Missing argument\n";
    return 1;
  }

  std::ifstream in(argv[1]);

  if (!in)
  {
    std::cerr << "Could not open file\n";
    return 1;
  }

  Lexer lexer(in);

  Token token = lexer.nextToken();
  while (token != Token::END_OF_FILE)
  {
    std::cout << "Token: " << Lexer::tokenToString(token) << ", text: " << lexer.getText() << "\n";
    token = lexer.nextToken();
  }

  in.close();
  return 0;
}
