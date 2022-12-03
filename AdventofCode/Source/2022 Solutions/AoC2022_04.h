template<> Number AoC<2022, 4, A>(std::istream& input)
{
  return 0;

  std::vector<std::string> v = ReadLines(input);
  Number z = 0;

  for (const auto& line : v)
  {
    bool exist[52]{ false };
    for (int i = 0; i < line.size() / 2; ++i)
    {
      const char& c = line[i];
      int index;
      if (c < 'a') index = c - 'A' + 26;
      else index = c - 'a';
      exist[index] = true;
    }

    for (int i = 0; i < line.size() / 2; ++i)
    {
      const char& c = line[line.size() / 2 + i];
      int index;
      if (c < 'a') index = c - 'A' + 26;
      else index = c - 'a';
      if (exist[index])
      {
        z += index + 1;
        break;
      }
    }
  }
  return z;
}

template<> Number AoC<2022, 4, B>(std::istream& input)
{
  return 0;

  std::vector<std::string> v = ReadLines(input);
  Number z = 0;
  Number n = 0;

  for (int j = 0; j < v.size(); j += 3)
  {
    bool exist1[52]{ false };
    bool exist2[52]{ false };
    for (int i = 0; i < v[j].size(); ++i)
    {
      const char& c = v[j][i];
      int index;
      if (c < 'a') index = c - 'A' + 26;
      else index = c - 'a';
      exist1[index] = true;
    }

    for (int i = 0; i < v[j + 1].size(); ++i)
    {
      const char& c = v[j + 1][i];
      int index;
      if (c < 'a') index = c - 'A' + 26;
      else index = c - 'a';
      exist2[index] = true;
    }

    for (int i = 0; i < v[j + 2].size(); ++i)
    {
      const char& c = v[j + 2][i];
      int index;
      if (c < 'a') index = c - 'A' + 26;
      else index = c - 'a';
      if (exist1[index] && exist2[index])
      {
        z += index + 1;
        n++;
        break;
      }
    }
  }
  return z;
}

