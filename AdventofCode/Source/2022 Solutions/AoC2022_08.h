template<> Number AoC<2022, 8, A>(std::istream& input)
{

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<std::vector<bool>> visible{ false };

  visible.resize(v.size());
  for (int i = 0; i < v.size(); ++i) visible[i].resize(v[0].size());

  for (int x = 0; x < v[0].size(); ++x)
  {
    int sofar = 0;
    for (int y = 0; y < v.size(); ++y)
    {
      if (v[x][y] > sofar)
      {
        visible[x][y] = true;
        sofar = v[x][y];
      }
    }

    sofar = 0;
    for (int y = v.size()-1; y >=0; --y)
    {
      if (v[x][y] > sofar)
      {
        visible[x][y] = true;
        sofar = v[x][y];
      }
    }
  }
  for (int y = 0; y < v.size(); ++y)  
  {
    int sofar = 0;
    for (int x = 0; x < v[0].size(); ++x)
    {
      if (v[x][y] > sofar)
      {
        visible[x][y] = true;
        sofar = v[x][y];
      }
    }

    sofar = 0;
    for (int x = v[0].size()-1; x>=0; --x)
    {
      if (v[x][y] > sofar)
      {
        visible[x][y] = true;
        sofar = v[x][y];
      }
    }
  }

  Number z=0;
  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[0].size(); ++x)
    {
      if (visible[x][y]) ++z;
    }
  }
  return z;
}

template<> Number AoC<2022, 8, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector<std::vector<Number>> score{0};

  score.resize(v.size());
  for (int i = 0; i < v.size(); ++i) score[i].resize(v[0].size());

  
  for (int y = 0; y < v.size(); ++y)
  {
    for (int x = 0; x < v[0].size(); ++x)
    {
      score[x][y] = 1;

      Number z = 0;
      for (int dx = 1; dx <= v[0].size() - 1 - x; ++dx)  /// to the right
      {
        ++z;
        if (v[x + dx][y] >= v[x][y]) break;
      }
      score[x][y] *= z;

      z = 0;
      for (int dx = 1; dx <= x; ++dx)  /// to the left
      {
        ++z;
        if (v[x - dx][y] >= v[x][y]) break;
      }
      score[x][y] *= z;

      z = 0;
      for (int dy = 1; dy <= v.size() - 1 - y; ++dy)  /// to the bottom
      {
        ++z;
        if (v[x][y + dy] >= v[x][y]) break;
      }
      score[x][y] *= z;

      z = 0;
      for (int dy = 1; dy <= y; ++dy)  /// to the bottom
      {
        ++z;
        if (v[x][y - dy] >= v[x][y]) break;
      }
      score[x][y] *= z;
    }
  }

  
  Number mx = 0;
  for (int x = 0; x < v[0].size(); ++x)
  {
    for (int y = 0; y < v.size(); ++y)
    {
      if (score[x][y] > mx) mx = score[x][y];
    }
  }

  return mx;
}
