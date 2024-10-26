#include "token.hpp"

std::string tokenTypeToString(TokenType type) {
  if (type == TokenType::ILLEGAL)
    return "ILLEGAL";
  else if (type == TokenType::EOF_)
    return "EOF";
  else if (type == TokenType::INDENT)
    return "IDENT";
  else if (type == TokenType::INTEGER)
    return "INT";
  else if (type == TokenType::ASSIGN)
    return "=";
  else if (type == TokenType::PLUS)
    return "+";
  else if (type == TokenType::COMMA)
    return ",";
  else if (type == TokenType::SEMICOLON)
    return ";";
  else if (type == TokenType::L_PARENTHESIS)
    return "(";
  else if (type == TokenType::R_PARENTHESIS)
    return ")";
  else if (type == TokenType::L_BRACE)
    return "{";
  else if (type == TokenType::R_BRACE)
    return "}";
  else if (type == TokenType::FUNCTION)
    return "FUNCTION";
  else if (type == TokenType::LET)
    return "LET";
  else
    return "UNKNOWN";
}
