#include "token.hpp"
#include <map>
#include <string>

std::string Token::tokenTypeToString(TokenType type) {
  static const std::unordered_map<TokenType, std::string> tokenTypeMap = {
      {TokenType::ILLEGAL, "ILLEGAL"},
      {TokenType::EOF_, "EOF"},
      {TokenType::INDENT, "IDENT"},
      {TokenType::INTEGER, "INT"},
      {TokenType::ASSIGN, "="},
      {TokenType::PLUS, "+"},
      {TokenType::MINUS, "-"},
      {TokenType::BANG, "!"},
      {TokenType::ASTERISK, "*"},
      {TokenType::SLASH, "/"},
      {TokenType::LESSTHAN, "<"},
      {TokenType::GREATERTHAN, ">"},
      {TokenType::COMMA, ","},
      {TokenType::SEMICOLON, ";"},
      {TokenType::L_PARENTHESIS, "("},
      {TokenType::R_PARENTHESIS, ")"},
      {TokenType::L_BRACE, "{"},
      {TokenType::R_BRACE, "}"},
      {TokenType::LET, "LET"},
      {TokenType::FUNCTION, "FUNCTION"},
      {TokenType::TRUE, "TRUE"},
      {TokenType::FALSE, "FALSE"},
      {TokenType::IF, "IF"},
      {TokenType::ELSE, "ELSE"},
      {TokenType::RETURN, "RETURN"},
      {TokenType::EQUALS, "EQUAL"},
      {TokenType::NOT_EQUALS, "NOT_EQUAL"},
  };

  const auto it = tokenTypeMap.find(type);
  if (it != tokenTypeMap.end()) {
    return it->second;
  } else {
    return "UNKNOWN";
  }
}

TokenType Token::lookUpIndent(const std::string indent) {
  const auto it = keywords.find(indent);
  if (it != keywords.end()) {
    return it->second;
  }

  return TokenType::INDENT;
}

// Private
//
std::map<std::string, TokenType> Token::keywords = {
    {"fn", TokenType::FUNCTION},   {"let", TokenType::LET},
    {"true", TokenType::TRUE},     {"false", TokenType::FALSE},
    {"if", TokenType::IF},         {"else", TokenType::ELSE},
    {"return", TokenType::RETURN},
};
