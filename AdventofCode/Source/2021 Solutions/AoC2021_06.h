template<> Number AoC<2021, 6, A>(std::istream& input)
{
  std::string line{};
  getline(input, line);

  std::vector<int> f{};

  std::istringstream str(line);
  int z{ 0 };
  while (str >> z)
  {
    f.emplace_back(z);
    char comma{};
    str >> comma;
  }

  for (int i = 0; i < 80; ++i)
  {
    int n{ 0 };  // new fish
    for (auto& fish : f)
    {
      if (--fish < 0)
      {
        fish = 6;
        ++n;
      }
    }
    for (int j = 0; j < n; ++j) f.emplace_back(8);
  }

  return f.size();
}


template<> Number AoC<2021, 6, B>(std::istream& input)
{
  std::string line{};
  getline(input, line);

  std::vector<int> f{};
  std::vector<long long> ff{};

  std::istringstream str(line);
  int z{ 0 };
  while (str >> z)
  {
    f.emplace_back(z);
    ff.emplace_back(1);
    char comma{};
    str >> comma;
  }

  for (int i = 0; i < 256; ++i)
  {
    long long n{ 0 };  // new fish
    for (int k = 0; k < f.size(); ++k)
    {
      if (--f[k] < 0)
      {
        f[k] = 6;
        n += ff[k];
      }
    }
    if (n > 0)
    {
      f.emplace_back(8);
      ff.emplace_back(n);
    }
  }

  Number z00{ 0 };
  for (size_t i = 0; i < f.size(); ++i) z00 += ff[i];

  return z00;
}

