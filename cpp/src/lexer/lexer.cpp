#include "lexer.hpp"
#include "token/token.hpp"
#include <iostream>
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

  eatWhiteSpace();

  switch (ch) {
  case '=':
    if (peekChar() == '=') {
      std::cout << "Peak Value is: " << std::string(1, ch) << std::endl;
      const auto curr_ch = ch;
      readChar();

      const Token token = Token(TokenType::EQUALS,
                                std::string(1, curr_ch) + std::string(1, ch));

      readChar(); // This is to skip the inner value we picked into
      return token;
    } else {
      return createToken(TokenType::ASSIGN, std::string(1, ch));
    }

  case ';':
    return createToken(TokenType::SEMICOLON, std::string(1, ch));

  case '(':
    return createToken(TokenType::L_PARENTHESIS, std::string(1, ch));

  case ')':
    return createToken(TokenType::R_PARENTHESIS, std::string(1, ch));

  case ',':
    return createToken(TokenType::COMMA, std::string(1, ch));

  case '+':
    return createToken(TokenType::PLUS, std::string(1, ch));

  case '-':
    return createToken(TokenType::MINUS, std::string(1, ch));

  case '!':
    if (peekChar() == '=') {
      const auto curr_ch = ch;
      readChar();
      const Token token = Token(TokenType::NOT_EQUALS,
                                std::string(1, curr_ch) + std::string(1, ch));

      readChar(); // This is to skip the inner value we picked into
      return token;
    } else {
      return createToken(TokenType::BANG, std::string(1, ch));
    }

  case '/':
    return createToken(TokenType::SLASH, std::string(1, ch));

  case '*':
    return createToken(TokenType::ASTERISK, std::string(1, ch));

  case '<':
    return createToken(TokenType::LESSTHAN, std::string(1, ch));

  case '>':
    return createToken(TokenType::GREATERTHAN, std::string(1, ch));

  case '{':
    return createToken(TokenType::L_BRACE, std::string(1, ch));

  case '}':
    return createToken(TokenType::R_BRACE, std::string(1, ch));

  case 0:
    return createToken(TokenType::EOF_, std::string(1, ch));

  default:
    if (isLetter(ch)) {
      const std::string literal = readIndentifier();
      const TokenType type = Token::lookUpIndent(literal);

      // We are not using the createToken function here becase "readNumber()"
      // already call "readChar()" using the "createToken()" function will call
      // "readChar()" twice and cause use to skip two value.
      // This is a issues when you you have an example like this "let five = 5;"
      // especailly at "5;", skiping two char will cause invaild persing
      return Token(type, literal);
    } else if (isDigit(ch)) {
      const std::string literal = readNumber();

      return Token(TokenType::INTEGER, literal);
    } else {

      return createToken(TokenType::ILLEGAL, std::string(1, ch));
    }
  }
}

// Private Methods

Token Lexer::createToken(TokenType type, const std::string &value) {
  Token token(type, value);
  readChar();
  return token;
}

bool Lexer::isLetter(unsigned char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool Lexer::isDigit(unsigned char ch) {
  //
  return '0' <= ch && ch <= '9';
}

std::string Lexer::readIndentifier() {
  const size_t start_position = position;
  while (isLetter(ch)) {
    readChar();
  }

  return input.substr(start_position, position - start_position);
}

std::string Lexer::readNumber() {
  const size_t start_position = position;
  while (isDigit(ch)) {
    readChar();
  }

  return input.substr(start_position, position - start_position);
}

void Lexer::eatWhiteSpace() {
  while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
    readChar();
  }
}

unsigned char Lexer::peekChar() {
  if (readPosition >= input.size()) {
    return 0;
  } else {
    return input[readPosition];
  }
}
