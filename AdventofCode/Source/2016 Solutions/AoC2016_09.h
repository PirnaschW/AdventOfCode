//template<> auto InputData<2016, 9, A>() { return "X(8x2)(3x3)ABCY\n";}; // Result: X(3x3)ABC(3x3)ABCY
template<> Number AoC<2016, 9, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // X(8x2)(3x3)ABCY becomes X(3x3)ABC(3x3)ABCY

  std::string result{};
  result.reserve(v[0].size() * 12);

  for (int i = 0; i < v[0].size();)
  {
    switch (v[0][i])
    {
      default:
        result.push_back(v[0][i]);
        ++i;
        break;
      case '(':
      {
        int amount{ 0 };
        int repeat{ 0 };
        int offset{ 0 };
        ++i;
        int z = sscanf_s(v[0].data() + i, "%dx%d)%n", &amount, &repeat, &offset);
        assert(z == 2);
        i += offset;
        std::string piece = v[0].substr(i, amount);
        for (int j = 0; j < repeat; ++j)
        {
          result += piece;
        }
        i += amount;
      }
    }
  }

  return result.size();
}

//template<> auto InputData<2016, 9, B>() { return "X(8x2)(3x3)ABCY\n";}; // Result: 20
//template<> auto InputData<2016, 9, B>() { return "(27x12)(20x12)(13x14)(7x10)(1x12)A\n";}; // Result: 241920
template<> Number AoC<2016, 9, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // X(8x2)(3x3)ABCY becomes X(3x3)ABC(3x3)ABCY

  auto Decompress = [](const std::string& s, auto& Decompress) -> Number
    {

      Number lResult{ 0 };
      for (int i = 0; i < s.size();)
      {
        switch (s[i])
        {
          default:
            ++lResult;
            ++i;
            break;
          case '(':
          {
            int amount{ 0 };
            int repeat{ 0 };
            int offset{ 0 };
            ++i;
            int z = sscanf_s(s.data() + i, "%dx%d)%n", &amount, &repeat, &offset);
            assert(z == 2);
            i += offset;
            const std::string piece = s.substr(i, amount);
            Number l = Decompress(piece, Decompress);
            lResult += l * repeat;
            i += amount;
          }
        }
      }
      return lResult;
    };

  Number lResult = Decompress(v[0], Decompress);
  return lResult;
}
