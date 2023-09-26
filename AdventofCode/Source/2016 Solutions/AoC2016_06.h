//template<> auto InputData<2016, 6, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 6, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  std::vector<std::array<int, 26>> counts{};
  counts.resize(v[0].size());

  for (const auto& line : v)
  {
    for (int i = 0; i < line.size(); ++i)
    {
      ++counts[i][line[i] - 'a'];
    }
  }

  std::vector<int> maxn{};
  std::vector<char> maxc{};
  maxn.resize(v[0].size());
  maxc.resize(v[0].size());
  for (int i = 0; i < v[0].size(); ++i)
  {
    for (int j = 0; j < counts[0].size(); ++j)
    {
      if (counts[i][j] > maxn[i])
      {
        maxn[i] = counts[i][j];
        maxc[i] = j;
      }
    }
  }

  std::string result{};
  for (int i = 0; i < v[0].size(); ++i)
  {
    result += 'a' + maxc[i];
  }

  throw result;
}

//template<> auto InputData<2016, 6, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 6, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  std::vector<std::array<int, 26>> counts{};
  counts.resize(v[0].size());

  for (const auto& line : v)
  {
    for (int i = 0; i < line.size(); ++i)
    {
      ++counts[i][line[i] - 'a'];
    }
  }

  std::vector<int> minn{};
  std::vector<char> minc{};
  minn.resize(v[0].size());
  minc.resize(v[0].size());
  for (int i = 0; i < v[0].size(); ++i)
  {
    minn[i] = std::numeric_limits<int>::max();
    for (int j = 0; j < counts[0].size(); ++j)
    {
      if (counts[i][j] == 0) continue;
      if (counts[i][j] < minn[i])
      {
        minn[i] = counts[i][j];
        minc[i] = j;
      }
    }
  }

  std::string result{};
  for (int i = 0; i < v[0].size(); ++i)
  {
    result += 'a' + minc[i];
  }

  throw result;
}
