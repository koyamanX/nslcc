#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <variant>

enum class ReservedKeywordType {
    DECLARE,
    MODULE,
    RBRACE,
    LBRACE,
    INPUT,
    OUTPUT,
    INOUT,
    SEMICOLON,
    RBRACKET,
    LBRACKET,
    NUMBER,
    EoF,
};

using u64 = unsigned long long;
using u32 = unsigned int;
using u16 = unsigned short;
using u8 = unsigned char;
using i64 = long long;
using i32 = int;
using i16 = short;
using i8 = char;

using Identifier = std::string;
using Number = u64;

class Token {
    using TokenType = std::variant<ReservedKeywordType, Identifier, Number>;

   public:
    template <typename T>
    Token(T &&value) : value(std::forward<T>(value)){};
    ~Token() = default;

    template <typename T>
    constexpr bool is() const noexcept {
        return std::holds_alternative<T>(value);
    }

    template <typename T>
    constexpr bool isNot() const noexcept {
        return !is<T>();
    }

    template <typename T>
    constexpr const T &get() const noexcept {
        return std::get<T>(value);
    }

    template <typename T>
    bool operator==(const T &rhs) const noexcept {
        return std::holds_alternative<T>(value) && std::get<T>(value) == rhs;
    }

    template <typename T>
    bool operator!=(const T &rhs) const noexcept {
        return !(*this == rhs);
    }

   private:
    TokenType value;
};

#endif  // TOKEN_HPP
