// #pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

#include "src/token/token.hpp"
#include <string>
#include <sys/stat.h>

struct Lexer {
  std::string input;
  unsigned int position;
  unsigned int readPosition;
  unsigned char ch;

  Lexer(const std::string &inp);

  static Lexer *New(const std::string &input);

  void readChar();

  Token nextToken();

private:
  Token createToken(TokenType type, unsigned char ch);
};

#endif // LEXER_HPP
