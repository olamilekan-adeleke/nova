#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <map>
#include <string>

enum class TokenType {
  ILLEGAL,
  EOF_,

  // Identifiers + literals
  INDENT,
  INTEGER,

  // Operators
  ASSIGN,
  PLUS,

  // Delimiters
  COMMA,
  SEMICOLON,

  L_PARENTHESIS,
  R_PARENTHESIS,
  L_BRACE,
  R_BRACE,

  // Lang Keyword
  LET,
  FUNCTION,

};

struct Token {
  TokenType type;
  std::string literal;

  Token(TokenType t, const std::string &lit) : type(t), literal(lit) {}

  std::string tokenTypeToString(TokenType type); // TODO: Test

  static TokenType lookUpIndent(const std::string ident); // TODO: Test

private:
  static std::map<std::string, TokenType> keywords; // TODO: Test
};

#endif
