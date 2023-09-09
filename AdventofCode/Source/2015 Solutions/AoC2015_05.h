//template<> auto InputData<2015, 5, A>() { return "ugknbfddgicrmopn\n";}; // Result: nice
//template<> auto InputData<2015, 5, A>() { return "aaa\n";}; // Result: nice
//template<> auto InputData<2015, 5, A>() { return "jchzalrnumimnmhp\n";}; // Result: naugthy
//template<> auto InputData<2015, 5, A>() { return "haegwjzuvuyypxyu\n";}; // Result: naugthy
//template<> auto InputData<2015, 5, A>() { return "dvszwmarrgswjxmb\n";}; // Result: naughty
template<> Number AoC<2015, 5, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number nice{ 0 };
  for (const std::string& line : v)
  {
    int vowels{ 0 };
    bool twice{ false };
    bool badpair{ false };

    for (int i = 0; i < line.size(); ++i)
    {
      switch (line[i])
      {
        case 'a' :
        case 'e' :
        case 'i' :
        case 'o' :
        case 'u' :
          ++vowels;
          break;
      }

      if (i > 0)
      {
        if (line[i] == line[i - 1]) twice = true;

        if (line[i] == 'b' && line[i - 1] == 'a') badpair = true;
        if (line[i] == 'd' && line[i - 1] == 'c') badpair = true;
        if (line[i] == 'q' && line[i - 1] == 'p') badpair = true;
        if (line[i] == 'y' && line[i - 1] == 'x') badpair = true;
      }
      if (badpair) break;
    }

    if (!badpair && twice && vowels > 2) ++nice;
  }

  return nice;
}

//template<> auto InputData<2015, 5, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 5, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number nice{ 0 };
  for (const std::string& line : v)
  {
    bool repeat1{ false };
    bool repeat2{ false };
    for (int i = 0; i < line.size(); ++i)
    {
      if (i > 0)
      {
        for (int j = i + 2; j < line.size(); ++j)
        {
          if (line[j] == line[i] && line[j - 1] == line[i - 1]) repeat1 = true;
        }
      }
      if (i > 1)
      {
        if (line[i] == line[i - 2]) repeat2 = true;
      }
      if (repeat1 && repeat2) break;
    }
    if (repeat1 && repeat2) ++nice;
  }

  return nice;
}
