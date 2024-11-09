#include "token/token.hpp"
#include <gtest/gtest.h>

// Test for tokenTypeToString mapping
TEST(TokenTest, tokenTypeToString) {
  // Known token types
  EXPECT_EQ(Token::tokenTypeToString(TokenType::INTEGER), "INT");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::ILLEGAL), "ILLEGAL");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::EOF_), "EOF");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::INDENT), "IDENT");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::ASSIGN), "=");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::PLUS), "+");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::MINUS), "-");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::BANG), "!");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::ASTERISK), "*");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::SLASH), "/");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::LESSTHAN), "<");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::GREATERTHAN), ">");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::COMMA), ",");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::SEMICOLON), ";");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::L_PARENTHESIS), "(");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::R_PARENTHESIS), ")");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::L_BRACE), "{");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::R_BRACE), "}");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::LET), "LET");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::FUNCTION), "FUNCTION");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::TRUE), "TRUE");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::FALSE), "FALSE");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::IF), "IF");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::ELSE), "ELSE");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::RETURN), "RETURN");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::EQUALS), "EQUAL");
  EXPECT_EQ(Token::tokenTypeToString(TokenType::NOT_EQUALS), "NOT_EQUAL");

  // Edge case: Unknown token type (assuming you might have a placeholder or
  // unmapped value)
  EXPECT_EQ(Token::tokenTypeToString(static_cast<TokenType>(999)), "UNKNOWN");
}

TEST(TokenTest, testTokenTypeToString) {
  Token token(TokenType::INTEGER, "5");
  EXPECT_EQ(Token::tokenTypeToString(token.type), "INT");

  Token token2(TokenType::ILLEGAL, "//");
  EXPECT_EQ(Token::tokenTypeToString(token2.type), "ILLEGAL");
}

TEST(TokenTest, RecognizesKeywords) {
  EXPECT_EQ(Token::lookUpIndent("fn"), TokenType::FUNCTION);
  EXPECT_EQ(Token::lookUpIndent("let"), TokenType::LET);
  EXPECT_EQ(Token::lookUpIndent("true"), TokenType::TRUE);
  EXPECT_EQ(Token::lookUpIndent("false"), TokenType::FALSE);
  EXPECT_EQ(Token::lookUpIndent("if"), TokenType::IF);
  EXPECT_EQ(Token::lookUpIndent("else"), TokenType::ELSE);
  EXPECT_EQ(Token::lookUpIndent("return"), TokenType::RETURN);
}

// Test case for unknown identifiers
TEST(TokenTest, ReturnsIndentForUnknownIdentifiers) {
  EXPECT_EQ(Token::lookUpIndent("unknown"), TokenType::INDENT);
  EXPECT_EQ(Token::lookUpIndent("not_a_keyword"), TokenType::INDENT);
}

// Edge case test for empty string input
TEST(TokenTest, ReturnsIndentForEmptyString) {
  EXPECT_EQ(Token::lookUpIndent(""), TokenType::INDENT);
}
