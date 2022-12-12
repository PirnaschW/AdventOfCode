template<> Number AoC<2022, 6, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  char l[4]{};
  int index = 0;


  for (int j = 0; j < v.size(); ++j)
  {
    const std::string& line = v[j];
    for (int i = 0; i < line.size(); ++i)
    {
      bool cont = false;
      l[index++] = line[i];
      index %= 4;
      for (int z = 0; z < 4; z++)
        for (int y = z + 1; y < 4; y++)
          if (l[z] == l[y] || l[y] == 0)
          {
            cont = true;
            break;
          }
      if (!cont) return i + 1;
    }
  }
  return -1;
}

template<> Number AoC<2022, 6, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  char l[14]{};
  int index = 0;


  for (int j = 0; j < v.size(); ++j)
  {
    const std::string& line = v[j];
    for (int i = 0; i < line.size(); ++i)
    {
      bool cont = false;
      l[index++] = line[i];
      index %= 14;
      for (int z = 0; z < 14; z++)
        for (int y = z + 1; y < 14; y++)
          if (l[z] == l[y] || l[y] == 0)
          {
            cont = true;
            break;
          }
      if (!cont) return i + 1;
    }
  }
  return -1;
}

