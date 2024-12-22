//template<> auto InputData<2015, 12, A>() { return R"--([1,2,3])--"                "\n"; }; // Result: 6
//template<> auto InputData<2015, 12, A>() { return R"--({"a":2,"b":4})--"          "\n"; }; // Result: 6
//template<> auto InputData<2015, 12, A>() { return R"--([[[3]]])--"                "\n"; }; // Result: 3
//template<> auto InputData<2015, 12, A>() { return R"--({"a":{"b":4},"c":-1})--"   "\n"; }; // Result: 3
//template<> auto InputData<2015, 12, A>() { return R"--({"a":[-1,1]})--"           "\n"; }; // Result: 0
//template<> auto InputData<2015, 12, A>() { return R"--([-1,{"a":1}])--"           "\n"; }; // Result: 0
template<> Number AoC<2015, 12, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number z{ 0 };
  Number num{ 0 };
  bool minus{ false };
  for (const auto& line : v)
  {
    for (const auto& c : line)
    {
      if (c == '-')
      {
        minus = true;
      }
      else if (isdigit(c))
      {
        num *= 10;
        num += c - '0';
      }
      else
      {
        z += minus ? -num : num;
        num = 0;
        minus = false;
      }
    }
  }
  return z;
}

//template<> auto InputData<2015, 12, B>() { return R"--([1,2,3])--"                          "\n"; }; // Result: 6
//template<> auto InputData<2015, 12, B>() { return R"--([1,{"c":"red","b":2},3])--"          "\n"; }; // Result: 4
//template<> auto InputData<2015, 12, B>() { return R"--({"d":"red","e":[1,2,3,4],"f":5})--"  "\n"; }; // Result: 0
//template<> auto InputData<2015, 12, B>() { return R"--([1,"red",5])--"                      "\n"; }; // Result: 6
template<> Number AoC<2015, 12, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  
  class H
  {
  public:
    static Number Sum(const char*& cur, const char endat, bool& match)
    {
      Number z{ 0 };
      Number num{ 0 };
      bool minus{ false };
      match = false;
      while (true)
      {
        switch (*cur)
        {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            num *= 10;
            num += *cur - '0';
            ++cur;
            continue;
          default:
            z += minus ? -num : num;
            num = 0;
            minus = false;
            if (*cur == endat) return z;
        }
        assert(*cur != endat);
        assert(*cur != '\0');
        switch (*cur)
        {
          case '[': z += SumArray(++cur);  break;
          case '{': z += SumObject(++cur); break;
          case '-': minus = true; ++cur;  break;
          case '\"': match |= CheckAttribute(++cur, "red"); break;
          default: ++cur; break;
        }
      }
    }
    static bool CheckAttribute(const char*& cur, const std::string& check)
    {
      unsigned int i{ 0 };
      bool match = { true };
      while (*cur != '\"')
      {
        if (i >= check.size() || *cur != check[i]) match = false;
        ++i;
        ++cur;
      }
      assert(*cur == '\"');
      ++cur;
      return match;
    }
    static Number SumArray(const char*& cur)
    {
      bool match{ false };
      Number z = Sum(cur, ']', match);
      assert(*cur == ']');
      ++cur;
      return z;
    }
    static Number SumObject(const char*& cur)
    {
      bool match{ false };
      Number z = Sum(cur, '}', match);
      assert(*cur == '}');
      ++cur;
      return match ? 0 : z;
    }
  };

  const char* cur = v[0].c_str();
  bool match{ false };
  Number z = H::Sum(cur, '\0', match);
  
  return z;
}
