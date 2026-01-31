#include "Lexer.h"
#include <cctype>
#include <cstdlib>
#include <cstring>

// Constant Array of Keywords in a sorted manner,
// Strings are searched using bsearch
// clang-format off
const Keywords::Mapping Keywords::m_Mappings[] = {
    {NULL, KEYWORD_ILLEGAL},
    {"and", KEYWORD_AND},
    {"break", KEYWORD_BREAK},
    {"do", KEYWORD_DO},
    {"else", KEYWORD_ELSE},
    {"elseif", KEYWORD_ELSEIF},
    {"end", KEYWORD_END},
    {"false", KEYWORD_FALSE},
    {"for", KEYWORD_FOR},
    {"function", KEYWORD_FUNCTION},
    {"main", KEYWORD_MAIN},
    {"if", KEYWORD_IF},
    {"in", KEYWORD_IN},
    {"local", KEYWORD_LOCAL},
    {"nil", KEYWORD_NIL},
    {"not", KEYWORD_NOT},
    {"or", KEYWORD_OR},
    {"repeat", KEYWORD_REPEAT},
    {"return", KEYWORD_RETURN},
    {"then", KEYWORD_THEN},
    {"true", KEYWORD_TRUE},
    {"until", KEYWORD_UNTIL},
    {"while", KEYWORD_WHILE},
};
// clang-format on

const int Keywords::m_Count =
    (const int)(sizeof(Keywords::m_Mappings) / sizeof(Keywords::m_Mappings[0]));

struct Keywords_search_keys
{
    const char *key;
    size_t size;
};

static int CompareKeywords(const void *keyv, const void *mapv)
{
    const Keywords_search_keys *key =
        static_cast<const Keywords_search_keys *>(keyv);
    const Keywords::Mapping *map = static_cast<const Keywords::Mapping *>(mapv);
    if (map->Keystring == NULL) {
        return 1;
    }
    int i = strcmp(key->key, map->Keystring);
    if (i != 0) {
        return 1;
    } else {
        return 0;
    }
}

Keyword Keywords::KeywordToCode(const char *keystring, size_t len) const
{
    Keywords_search_keys key;
    key.key = keystring;
    key.size = len;
    void *mapv = std::bsearch(&key, this->m_Mappings, this->m_Count,
                              sizeof(this->m_Mappings[0]), CompareKeywords);
    if (mapv == NULL) {
        return KEYWORD_ILLEGAL;
    }
    Mapping *map = static_cast<Mapping *>(mapv);
    return map->Keycode;
}

TokenType gettok()
{
    // Why would you set it to whitespace first
    static int LastChar = ' ';
    while (isspace(LastChar)) {
        LastChar = getchar();
    }
    // Check for comment
    // Now this lua supports # for comments rather than --
    if (LastChar == '#') {
        do {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
        if (LastChar != EOF) {
            return gettok();
        }
    }
    if (std::isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (std::isalnum(LastChar)) {
            IdentifierStr += LastChar;
            LastChar = getchar();
        }
        Keywords keywords;
        Keyword keytoken =
            keywords.KeywordToCode(IdentifierStr.c_str(), IdentifierStr.size());
        if (keytoken == KEYWORD_ILLEGAL) {
            return TOK_IDENTIFIER;
        } else {
            return TOK_KEYWORD;
        }
    } else if (std::isdigit(LastChar)) {
        std::string NumStr;
        NumStr += LastChar;
        while (std::isdigit(LastChar) || LastChar == '.') {
            // TODO: make sure that it's only valid for onetime . not more than
            // one Ex: 0.124 is right but 1.2.3 is wrong
            NumStr += LastChar;
        }
        NumVal = std::strtod(NumStr.c_str(), NULL);
        return TOK_NUMVAL;
    } else if (LastChar == EOF) {
        return TOK_EOF;
    } else {
        LastChar = getchar();
        switch (LastChar) {
        case '+': {
            return TOK_OPERATOR_ADD;
        } break;
        case '-': {
            return TOK_OPERATOR_SUB;
        } break;
        case '*': {
            return TOK_OPERATOR_MUL;
        } break;
        case '/': {
            return TOK_OPERATOR_DIV;
        } break;
        default: {
        }
        };
    }
    return TOK_ILLEGAL;
}
