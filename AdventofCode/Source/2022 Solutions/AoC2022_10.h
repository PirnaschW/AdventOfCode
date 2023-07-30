template<> Number AoC<2022, 10, A>(std::istream& input)
{
  struct H
  {
    static bool tick(Number& z)
    {
      ++z;
      return (z + 20) % 40;
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  Number z = 0;
  Number sum = 0;
  Number reg = 1;
  for (const auto& line : v)
  {
    if (!H::tick(z))
      sum += z * reg;

    if (line[0] != 'n')
    {
      if (!H::tick(z))
        sum += z * reg;
      std::istringstream str(line.substr(5));
      Number s{};
      str >> s;
      reg += s;
    }
    if (z > 220) break;
  }

  return sum;
}

template<> Number AoC<2022, 10, B>(std::istream& input)
{
  struct H
  {
    static void tick(Number& z, const Number& reg, std::string& res)
    {
      bool sprite = reg + 1 == z % 40 || reg == z % 40 || reg - 1 == z % 40;
      char c = sprite ? '#' : ' ';
      res += c;
      //std::cout << c;
      ++z;
      if (!(z % 40)) {
        res += '\n';
        //std::cout << '\n';
      }
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  Number z = 0;
  Number reg = 1;

  std::string result{};
  result += '\n';
//  std::cout << '\n';
  for (const auto& line : v)
  {
    H::tick(z, reg, result);

    if (line[0] != 'n')
    {
      H::tick(z, reg, result);
      std::istringstream str(line.substr(5));
      Number s{};
      str >> s;
      reg += s;
    }
  }

  throw result;
}
