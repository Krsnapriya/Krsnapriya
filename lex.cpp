#include <iostream>  
#include <string>    
#include <vector>    
#include <cctype>    

using namespace std;

const int MAX_LENGTH = 100; 

enum class TokenType {
    UNKNOWN,    
    KEYWORD,    
    IDENTIFIER, 
    OPERATOR,   
    INTEGER     
};

bool isOperator(char chr) {
    return (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '>' || 
            chr == '<' || chr == '=' || chr == '!' || chr == '&' || chr == '|' || 
            chr == '^' || chr == '%');
}

bool isValidIdentifier(const string& str) {
    if (str.empty() || (!isalpha(str[0]))) return false;
    
    for (size_t i = 1; i < str.length(); i++) {
        if (!isalnum(str[i])) return false;
    }
    return true;
}

bool isKeyword(const string& str) {
    static const vector<string> keywords = {
        "break", "auto", "case", "return", "const", "signed", "default", "do",
        "double", "else", "enum", "extern", "short", "for", "goto", "if",
        "int", "long", "register", "char", "float", "continue", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    
    for (const auto& keyword : keywords) {
        if (str == keyword) return true;
    }
    return false;
}

bool isInteger(const string& str) {
    if (str.empty()) return false;
    
    size_t i = 0;
    if (str[0] == '-') i++;
    if (i >= str.length()) return false;
    
    for (; i < str.length(); i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

void displayToken(TokenType type, const string& value) {
    switch (type) {
        case TokenType::KEYWORD:
            cout << "Token: Keyword, Value: " << value << endl;
            break;
        case TokenType::IDENTIFIER:
            cout << "Token: Identifier, Value: " << value << endl;
            break;
        case TokenType::OPERATOR:
            cout << "Token: Operator, Value: " << value << endl;
            break;
        case TokenType::INTEGER:
            cout << "Token: Integer, Value: " << value << endl;
            break;
        case TokenType::UNKNOWN:
            cout << "Token: Unknown, Value: " << value << endl;
            break;
    }
}

void lexicalAnalyzer(const string& input) {
    size_t left = 0, right = 0;
    size_t len = input.length();

    while (right <= len && left <= right) {
        while (right < len && input[right] == ' ') {
            right++;
        }

        if (right < len && isOperator(input[right])) {
            string operatorStr(1, input[right]);
            displayToken(TokenType::OPERATOR, operatorStr);
            right++;
            left = right;
        }
        else if (right < len && isalpha(input[right])) {
            left = right;
            while (right < len && isalnum(input[right])) {
                right++;
            }
            string subStr = input.substr(left, right - left);
            
            if (isKeyword(subStr)) {
                displayToken(TokenType::KEYWORD, subStr);
            }
            else if (isInteger(subStr)) {
                displayToken(TokenType::INTEGER, subStr);
            }
            else if (isValidIdentifier(subStr)) {
                displayToken(TokenType::IDENTIFIER, subStr);
            }
            else {
                displayToken(TokenType::UNKNOWN, subStr);
            }
            left = right;
        }
        else {
            right++;
            left = right;
        }
    }
}

int main() {
    string lex_input = "int a = b + c";
    cout << "For Expression \"" << lex_input << "\":" << endl;
    lexicalAnalyzer(lex_input);
    cout << endl;

    string lex_input01 = "int x = 8z + 9y + switch + 0y";
    cout << "For Expression \"" << lex_input01 << "\":" << endl;
    lexicalAnalyzer(lex_input01);
    cout << endl;

    return 0;
}