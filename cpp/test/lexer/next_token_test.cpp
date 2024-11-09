#include "src/lexer/lexer.hpp"
#include "src/token/token.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>
#include <string>

TEST(NextTokenTest, BasicAssertions) {
  std::string input = "=+(){},;";

  std::array<Token, 8> expected_tokens = {
      Token(TokenType::ASSIGN, std::string("=")),
      Token(TokenType::PLUS, std::string("+")),
      Token(TokenType::L_PARENTHESIS, std::string("(")),
      Token(TokenType::R_PARENTHESIS, std::string(")")),
      Token(TokenType::L_BRACE, std::string("{")),
      Token(TokenType::R_BRACE, std::string("}")),
      Token(TokenType::COMMA, std::string(",")),
      Token(TokenType::SEMICOLON, std::string(";")),
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
