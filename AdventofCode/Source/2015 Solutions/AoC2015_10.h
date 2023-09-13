//template<> auto InputData<2015, 10, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 10, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  // 3113322113

  std::string s0 = v[0];
  for (auto i = 0; i < 40; ++i)
  {
    std::string s1{};

    char curr{'\0'};
    int count{ 0 };
    for (const char& c : s0)
    {
      if (c == curr)
      {
        ++count;
      }
      else
      {
        if (curr != '\0')
        {
          s1.push_back(static_cast<char>('0'+count));
          s1.push_back(curr);
        }
        curr = c;
        count = 1;
      }
    }
    if (curr != '\0')
    {
      s1.push_back(static_cast<char>('0'+count));
      s1.push_back(curr);
    }
    std::swap(s0,s1);
  }
  return s0.size();
}

//template<> auto InputData<2015, 10, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 10, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  // 3113322113

  std::string s0 = v[0];
  for (auto i = 0; i < 50; ++i)
  {
    std::string s1{};

    char curr{'\0'};
    int count{ 0 };
    for (const char& c : s0)
    {
      if (c == curr)
      {
        ++count;
      }
      else
      {
        if (curr != '\0')
        {
          s1.push_back(static_cast<char>('0'+count));
          s1.push_back(curr);
        }
        curr = c;
        count = 1;
      }
    }
    if (curr != '\0')
    {
      s1.push_back(static_cast<char>('0'+count));
      s1.push_back(curr);
    }
    std::swap(s0,s1);
  }
  return s0.size();
}
