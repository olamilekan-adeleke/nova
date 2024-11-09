#include "lexer.hpp"
#include "src/token/token.hpp"
#include <string>
#include <sys/fcntl.h>

Lexer::Lexer(const std::string &inp)
    : input(inp), position(0), readPosition(0), ch(0) {}

// TODO: Maybe look into smart pointer
Lexer *Lexer::New(const std::string &input) {
  // return a new instance,
  Lexer *lexer = new Lexer(input);
  lexer->readChar();
  return lexer;
}

void Lexer::readChar() {
  if (readPosition >= input.size()) {
    ch = 0;
  } else {
    ch = input[readPosition];
  }

  position = readPosition;
  readPosition += 1;
}

Token Lexer::nextToken() {

  switch (ch) {
  case '=':
    return createToken(TokenType::ASSIGN, ch);

  case ';':
    return createToken(TokenType::SEMICOLON, ch);

  case '(':
    return createToken(TokenType::L_PARENTHESIS, ch);

  case ')':
    return createToken(TokenType::R_PARENTHESIS, ch);

  case ',':
    return createToken(TokenType::COMMA, ch);

  case '+':
    return createToken(TokenType::PLUS, ch);

  case '{':
    return createToken(TokenType::L_BRACE, ch);

  case '}':
    return createToken(TokenType::R_BRACE, ch);

  case 0:
    return createToken(TokenType::EOF_, ch);

  default:
    return createToken(TokenType::ILLEGAL, ch);
  }
}

// Private Methods

Token Lexer::createToken(TokenType type, unsigned char ch) {
  Token token(type, std::string(1, ch));
  readChar();
  return token;
}
