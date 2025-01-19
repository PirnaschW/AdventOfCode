//template<> auto InputData<2024, 3, A>() { return "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))\n";}; // Result: 161
template<> Number AoC<2024, 3, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  auto ReadNumber = [](const char* p) -> Number
    {
      Number f{ 0 };
      while (isdigit(*p))
      {
        f *= 10;
        f += *p - '0';
        ++p;
      }
      return f;
    };

  constexpr unsigned int BufferLength{ 32 };
  Number res{ 0 };
  char s1[BufferLength]{};
  char s2[BufferLength]{};
  for (const auto& line : v)
  {
    for (int i = 0; i < std::size(line); ++i)
    {
      if (line[i] != 'm') continue; // just a shortcut
      int n{ 0 };
      int z = sscanf_s(line.c_str() + i, "mul(%[0-9],%[0-9])%n", s1, BufferLength, s2, BufferLength, &n);
      if (z != 2) continue;
      if (n == 0) continue;

      i += n - 1;
      Number f1 = ReadNumber(s1);
      Number f2 = ReadNumber(s2);
      res += f1 * f2;
    }
  }
  
  return res;
}

//template<> auto InputData<2024, 3, B>() { return "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))\n"; }; // Result: 48
template<> Number AoC<2024, 3, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  auto ReadNumber = [](const char* p) -> Number
    {
      Number f{ 0 };
      while (isdigit(*p))
      {
        f *= 10;
        f += *p - '0';
        ++p;
      }
      return f;
    };

  constexpr unsigned int BufferLength{ 32 };
  Number res{ 0 };
  char s1[BufferLength]{};
  char s2[BufferLength]{};
  bool enabled{ true };
  for (const auto& line : v)
  {
    for (int i = 0; i < std::size(line); ++i)
    {
      if (line[i] != 'm' && line[i] != 'd') continue; // just a shortcut
      int n{ 0 };

      sscanf_s(line.c_str() + i, "don't()%n", &n);
      if (n > 0)
      {
        i += n - 1;
        enabled = false;
        continue;
      }

      sscanf_s(line.c_str() + i, "do()%n", &n);
      if (n > 0)
      {
        i += n - 1;
        enabled = true;
        continue;
      }

      int z = sscanf_s(line.c_str() + i, "mul(%[0-9],%[0-9])%n", s1, BufferLength, s2, BufferLength, &n);
      if (z != 2) continue;
      if (n == 0) continue;

      i += n - 1;
      if (enabled)
      {
        Number f1 = ReadNumber(s1);
        Number f2 = ReadNumber(s2);
        res += f1 * f2;
      }
    }
  }

  return res;
}
