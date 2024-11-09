#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <gtest/gtest.h>
#include <iostream>
#include <ostream>
#include <string>

TEST(LexerText, TestSingleCharToken) {
  const std::string input = "=+(){},;";

  std::array<Token, 8> expected_tokens = {
      Token(TokenType::ASSIGN, "="),
      Token(TokenType::PLUS, "+"),
      Token(TokenType::L_PARENTHESIS, "("),
      Token(TokenType::R_PARENTHESIS, ")"),
      Token(TokenType::L_BRACE, "{"),
      Token(TokenType::R_BRACE, "}"),
      Token(TokenType::COMMA, ","),
      Token(TokenType::SEMICOLON, ";"),
  };

  Lexer *lexer = Lexer::New(input);

  for (size_t i = 0; i < expected_tokens.size(); i++) {
    Token token = lexer->nextToken();

    EXPECT_EQ(token.type, expected_tokens[i].type)
        << "Token type does not match";
    EXPECT_EQ(token.literal, expected_tokens[i].literal)
        << "Token literal does not match";
  }
}

TEST(LexerText, TestComplexInput) {
  // const char *input = "let five = 5;";
  const char *input = R"""(
let five = 5;
let ten = 10;

let add = fn(x, y) {
x + y;
};

let result = add(five, ten);
  )""";

  std::array<Token, 36> expected_tokens = {
      // std::array<Token, 5> expected_tokens = {
      Token(TokenType::LET, "let"),         Token(TokenType::INDENT, "five"),
      Token(TokenType::ASSIGN, "="),        Token(TokenType::INTEGER, "5"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),         Token(TokenType::INDENT, "ten"),
      Token(TokenType::ASSIGN, "="),        Token(TokenType::INTEGER, "10"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),         Token(TokenType::INDENT, "add"),
      Token(TokenType::ASSIGN, "="),        Token(TokenType::FUNCTION, "fn"),
      Token(TokenType::L_PARENTHESIS, "("), Token(TokenType::INDENT, "x"),
      Token(TokenType::COMMA, ","),         Token(TokenType::INDENT, "y"),
      Token(TokenType::R_PARENTHESIS, ")"), Token(TokenType::L_BRACE, "{"),
      Token(TokenType::INDENT, "x"),        Token(TokenType::PLUS, "+"),
      Token(TokenType::INDENT, "y"),        Token(TokenType::SEMICOLON, ";"),
      Token(TokenType::R_BRACE, "}"),       Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),         Token(TokenType::INDENT, "result"),
      Token(TokenType::ASSIGN, "="),        Token(TokenType::INDENT, "add"),
      Token(TokenType::L_PARENTHESIS, "("), Token(TokenType::INDENT, "five"),
      Token(TokenType::COMMA, ","),         Token(TokenType::INDENT, "ten"),
      Token(TokenType::R_PARENTHESIS, ")"), Token(TokenType::SEMICOLON, ";"),
  };

  Lexer *lexer = Lexer::New(input);
  for (size_t i = 0; i < expected_tokens.size(); i++) {
    Token token = lexer->nextToken();

    // std::cout << "==============" << std::endl;
    // std::cout << token.literal << std::endl;
    // std::cout << expected_tokens[i].literal << std::endl;
    // std::cout << "--------------" << std::endl;
    // std::cout << token.tokenTypeToString(token.type) << std::endl;
    // std::cout << token.tokenTypeToString(expected_tokens[i].type) <<
    // std::endl; std::cout << "==============" << std::endl;

    EXPECT_EQ(token.type, expected_tokens[i].type)
        << "tokens[" << i << "] - tokentype wrong. "
        << "expected=" << static_cast<int>(expected_tokens[i].type)
        << ", got=" << static_cast<int>(token.type);
    EXPECT_EQ(token.literal, expected_tokens[i].literal)
        << "tokens[" << i << "] - literal wrong. "
        << "expected=" << expected_tokens[i].literal
        << ", got=" << token.literal;
  }
}
