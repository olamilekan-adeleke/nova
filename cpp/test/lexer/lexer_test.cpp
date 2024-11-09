#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include <array>
#include <cstddef>
#include <cstdio>
#include <gtest/gtest.h>
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
!-/*5;
5 < 10 > 5;

if (5 < 10) {
  return true;
} else {
  return false;
}

11 == 11;
13 != 9;
  )""";

  std::array<Token, 69> expected_tokens = {
      Token(TokenType::LET, "let"),
      Token(TokenType::INDENT, "five"),
      Token(TokenType::ASSIGN, "="),
      Token(TokenType::INTEGER, "5"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),
      Token(TokenType::INDENT, "ten"),
      Token(TokenType::ASSIGN, "="),
      Token(TokenType::INTEGER, "10"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),
      Token(TokenType::INDENT, "add"),
      Token(TokenType::ASSIGN, "="),
      Token(TokenType::FUNCTION, "fn"),
      Token(TokenType::L_PARENTHESIS, "("),
      Token(TokenType::INDENT, "x"),
      Token(TokenType::COMMA, ","),
      Token(TokenType::INDENT, "y"),
      Token(TokenType::R_PARENTHESIS, ")"),
      Token(TokenType::L_BRACE, "{"),
      Token(TokenType::INDENT, "x"),
      Token(TokenType::PLUS, "+"),
      Token(TokenType::INDENT, "y"),
      Token(TokenType::SEMICOLON, ";"),
      Token(TokenType::R_BRACE, "}"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::LET, "let"),
      Token(TokenType::INDENT, "result"),
      Token(TokenType::ASSIGN, "="),
      Token(TokenType::INDENT, "add"),
      Token(TokenType::L_PARENTHESIS, "("),
      Token(TokenType::INDENT, "five"),
      Token(TokenType::COMMA, ","),
      Token(TokenType::INDENT, "ten"),
      Token(TokenType::R_PARENTHESIS, ")"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::BANG, "!"),
      Token(TokenType::MINUS, "-"),
      Token(TokenType::SLASH, "/"),
      Token(TokenType::ASTERISK, "*"),
      Token(TokenType::INTEGER, "5"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::INTEGER, "5"),
      Token(TokenType::LESSTHAN, "<"),
      Token(TokenType::INTEGER, "10"),
      Token(TokenType::GREATERTHAN, ">"),
      Token(TokenType::INTEGER, "5"),
      Token(TokenType::SEMICOLON, ";"),

      Token(TokenType::IF, "if"),
      Token(TokenType::L_PARENTHESIS, "("),
      Token(TokenType::INTEGER, "5"),
      Token(TokenType::LESSTHAN, "<"),
      Token(TokenType::INTEGER, "10"),
      Token(TokenType::R_PARENTHESIS, ")"),
      Token(TokenType::L_BRACE, "{"),
      Token(TokenType::RETURN, "return"),
      Token(TokenType::TRUE, "true"),
      Token(TokenType::SEMICOLON, ";"),
      Token(TokenType::R_BRACE, "}"),
      Token(TokenType::ELSE, "else"),
      Token(TokenType::L_BRACE, "{"),
      Token(TokenType::RETURN, "return"),
      Token(TokenType::FALSE, "false"),
      Token(TokenType::SEMICOLON, ";"),
      Token(TokenType::R_BRACE, "}"),

      Token(TokenType::INTEGER, "11"),
      Token(TokenType::EQUALS, "=="),
      Token(TokenType::INTEGER, "11"),
      Token(TokenType::SEMICOLON, ";"),

      // Token(TokenType::INTEGER, "13"),
      // Token(TokenType::NOT_EQUALS, "!="),
      // Token(TokenType::INTEGER, "9"),
      // Token(TokenType::SEMICOLON, ";"),
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
