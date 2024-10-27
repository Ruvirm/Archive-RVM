#include "lexer.h"

void Lexer::advance() {
    position++;
    if (position > text.length() - 1) {
        currentChar = '\0';
    } else {
        currentChar = text[position];
    }
}

char Lexer::peek() {
    size_t peekPos = position + 1;
    if (peekPos > text.length() - 1) {
        return '\0';
    } else {
        return text[peekPos];
    }
}

Token Lexer::number() {
    std::string result;
    bool hasDecimalPoint = false;

    while (currentChar >= '0' && currentChar <= '9') {
        result += currentChar;
        advance();
    }


    if (currentChar == '.') {
        hasDecimalPoint = true;
        result += currentChar;
        advance();


        while (currentChar >= '0' && currentChar <= '9') {
            result += currentChar;
            advance();
        }
    }

    return Token(TokenType::NUMBER, result);
}


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (currentChar != '\0') {
        if (currentChar == ' ') {
            advance();
            continue;
        }
        if (currentChar >= '0' && currentChar <= '9') {
            tokens.push_back(number());
            continue;
        }
        if (currentChar == '"') {
            advance();
            std::string result;
            while (currentChar != '"' && currentChar != '\0') {
                result += currentChar;
                advance();
            }
            if (currentChar == '"') {
                advance();
                tokens.push_back(Token(TokenType::STRING, result));
                continue;
            }
        }
        if (currentChar == '\'') {
            advance();
            std::string result;
            while (currentChar != '\'' && currentChar != '\0') {
                result += currentChar;
                advance();
            }
            if (currentChar == '\'') {
                advance();
                tokens.push_back(Token(TokenType::CHAR, result));
                continue;
            }
        }
        if (isalpha(currentChar)) {
            std::string result;
            while (isalnum(currentChar) || currentChar == '_') {
                result += currentChar;
                advance();
            }
            tokens.push_back(Token(TokenType::ID, result));
            continue;
        }
        if (currentChar == '+') {
            tokens.push_back(Token(TokenType::PLUS, "+"));
            advance();
            continue;
        }
        if (currentChar == '-') {
            tokens.push_back(Token(TokenType::MINUS, "-"));
            advance();
            continue;
        }
        if (currentChar == '*') {
            tokens.push_back(Token(TokenType::MULTIPLY, "*"));
            advance();
            continue;
        }
        if (currentChar == '/') {
            tokens.push_back(Token(TokenType::DIVIDE, "/"));
            advance();
            continue;
        }
        if (currentChar == '(') {
            tokens.push_back(Token(TokenType::LPAREN, "("));
            advance();
            continue;
        }
        if (currentChar == ')') {
            tokens.push_back(Token(TokenType::RPAREN, ")"));
            advance();
            continue;
        }
        advance();
    }
    tokens.push_back(Token(TokenType::END, ""));
    return tokens;
}