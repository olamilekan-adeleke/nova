// #pragma once
#ifndef LEXER_HPP
#define LEXER_HPP

#include "token/token.hpp"
#include <string>
#include <sys/stat.h>

struct Lexer {
  std::string input;
  size_t position;
  size_t readPosition;
  unsigned char ch;

  Lexer(const std::string &inp);

  static Lexer *New(const std::string &input);

  void readChar();

  Token nextToken();

private:
  Token createToken(TokenType type, const std::string &input);

  bool isLetter(unsigned char ch);

  bool isDigit(unsigned char ch);

  std::string readIndentifier();

  std::string readNumber();

  void eatWhiteSpace();

  unsigned char peekChar();
};

#endif // LEXER_HPP
