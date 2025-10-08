#include <catch2/catch_all.hpp>
#include <sstream>
#include <string>
#include <type_traits>
#include <iomanip.hpp>

TEST_CASE("iomanip::simple")
{
    std::stringstream s;
    s << "some text" << ioex::endm; // можно и без ioex, если тоже вынесешь endm наружу
    CHECK(s.str() == "some text[eol]\n");
}

TEST_CASE("iomanip::one_operand")
{
    std::stringstream s;
    static_assert(!std::is_same_v<decltype(s << ioex::sin), std::ostream&>);
    s << "some test " << ioex::sin << 0
      << " and " << ioex::sin << "pi"
      << ioex::sin << 0.0;
    CHECK(s.str() == "some test 0.0 and sin(pi)0.0");
}

TEST_CASE("iomanip::two_operands")
{
    std::stringstream s;
    static_assert(!std::is_same_v<decltype(s << ioex::add), std::ostream&>);
    static_assert(!std::is_same_v<decltype(s << ioex::add << 48), std::ostream&>);
    static_assert(std::is_same_v<decltype(s << ioex::add << 48 << 56), std::ostream&>);

    SECTION("int")
    {
        s << ioex::add << 124 << 589 << " == " << 713;
        CHECK(s.str() == "713 == 713");
    }

    SECTION("string")
    {
        using namespace std::literals;
        s << ioex::add << "abc"s << "efg"s << " text";
        CHECK(s.str() == "abcefg text");
    }

    SECTION("double")
    {
        s << "get => " << ioex::add << 45.89 << 32.177 << " <=";
        CHECK(s.str() == "get => 78.067 <=");
    }
}
