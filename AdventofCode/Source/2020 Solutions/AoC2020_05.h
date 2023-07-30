template<> Number AoC<2020, 05, A>(std::istream& input)
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string line;
  while (input >> line)
  {
    v.emplace_back(line);
  }

  std::vector<int> seat{};
  seat.reserve(v.size());
  int zmax{ 0 };
  for (const auto& s : v)
  {
    int z{ 0 };
    for (const auto c : s)
    {
      z *= 2;
      if (c == 'B' || c == 'R') ++z;
    }
    seat.emplace_back(z);
    if (z > zmax) zmax = z;
  }

  return zmax;
}

template<> Number AoC<2020, 05, B>(std::istream& input)
{
  std::vector<std::string> v{};
  v.reserve(1000);
  std::string line;
  while (input >> line)
  {
    v.emplace_back(line);
  }

  std::vector<int> seat{};
  seat.reserve(v.size());
  for (const auto& s : v)
  {
    int z{ 0 };
    for (const auto c : s)
    {
      z *= 2;
      if (c == 'B' || c == 'R') ++z;
    }
    seat.emplace_back(z);
  }
  std::sort(seat.begin(), seat.end());

  for (int i = 1; i < seat.size(); ++i)
  {
    if (seat[i - 1] != seat[i] - 1)
    {
      return seat[i] - 1;
      //std::cout << seat[i] - 1 << std::endl;
    }
  }
  assert(false);
  throw ' ';
}
