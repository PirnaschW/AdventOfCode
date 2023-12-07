//template<> auto InputData<2023, 1, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 1, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number sum{ 0 };

  auto GetFirstDigit = [](const std::string& line) -> int { size_t pos = line.find_first_of("0123456789"); return line[pos] - '0'; };
  auto GetLastDigit  = [](const std::string& line) -> int { size_t pos = line.find_last_of("0123456789"); return line[pos] - '0'; };

  for (const auto& line : v)
  {
    int z = GetFirstDigit(line) * 10 + GetLastDigit(line);
    sum += z;
  }

  return sum;
}

//template<> auto InputData<2023, 1, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2023, 1, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number sum{ 0 };

  const std::array<std::string, 10> numbers
  { {
    { "zero"  },
    { "one"   },
    { "two"   },
    { "three" },
    { "four"  },
    { "five"  },
    { "six"   },
    { "seven" },
    { "eight" },
    { "nine"  },
  } };

  auto GetFirstStringNumber = [&numbers](const std::string& line, size_t minpos, int number) -> int
    {
      for (int i = 0; i < numbers.size(); ++i)
      {
        size_t pos = line.find(numbers[i]);
        if (pos == std::string::npos) continue;
        if (pos < minpos)
        {
          minpos = pos;
          number = i;
        }
      }
      return number;
    };
  auto GetLastStringNumber = [&numbers](const std::string& line, size_t maxpos, int number) -> int
    {
      for (int i = 0; i < numbers.size(); ++i)
      {
        size_t pos = line.rfind(numbers[i]);
        if (pos == std::string::npos) continue;
        if (pos > maxpos)
        {
          maxpos = pos;
          number = i;
        }
      }
      return number;
    };

  auto GetFirstDigitPos = [](const std::string& line) -> size_t
    {
      return line.find_first_of("0123456789");
    };
  auto GetLastDigitPos  = [](const std::string& line) -> size_t
    {
      return line.find_last_of("0123456789");
    };

  for (const auto& line : v)
  {
    size_t pos1 = GetFirstDigitPos(line);
    size_t pos2 = GetLastDigitPos(line);

    int digit1 = GetFirstStringNumber(line,pos1,line[pos1]-'0');
    int digit2 = GetLastStringNumber(line,pos2,line[pos2]-'0');
    int z = digit1 * 10 + digit2;
    sum += z;
  }

  return sum;
}
