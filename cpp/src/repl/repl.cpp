#include "lexer/lexer.hpp"
#include "token/token.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

class REPL {
private:
  bool running = true;
  std::string prompt = ">> ";
  std::vector<std::string> history;

  std::string read() {

    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);

    if (!input.empty()) {
      history.push_back(input);
    }

    return input;
  }

  void eval(const std::string &input) {
    if (input == "exit" || input == "quit") {
      running = false;
      return;
    }

    if (input == "history") {
      for (size_t i = 0; i < history.size(); i++) {
        std::cout << i + 1 << ": " << history[i] << std::endl;
      }

      std::cout << "" << std::endl;
      return;
    }

    if (input == "help") {
      printf("Available commands: \n");
      printf("  help    - Show this help\n");
      printf("  exit    - Exit the REPL\n");
      printf("  history - Show command history\n\n");
      return;
    }

    Lexer *lexer = Lexer::New(input);
    bool shouldLoop = true;
    while (shouldLoop) {
      Token token = lexer->nextToken();

      std::cout << "{TokenType:" << token.tokenTypeToString(token.type) << ", "
                << token.literal << "}" << std::endl;

      if (token.type == TokenType::EOF_) {
        shouldLoop = false;
        std::cout << "" << std::endl;
      }
    }
  }

public:
  REPL() {}

  void run() {
    std::cout << "Nova REPL! (Type 'help' for more info )" << std::endl;

    while (running) {
      try {
        std::string input = read();
        if (!input.empty()) {
          eval(input);
        }

      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    }

    std::cout << "Exiting..." << std::endl;
  }
};
