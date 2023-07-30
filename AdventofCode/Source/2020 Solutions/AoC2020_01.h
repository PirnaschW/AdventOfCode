template<> Number AoC<2020, 1, A>(std::istream& input)
{
  int z = 0;
  std::unordered_set<int> s{};

  while (input >> z)
  {
    if (s.contains(2020 - z)) break;
    s.emplace(z);
  }
  //std::cout << z * (2020 - z) << std::endl;
  return z * (2020 - z);
}

template<> Number AoC<2020, 1, B>(std::istream& input)
{
  constexpr int Y{ 2020 };
  int z = 0;
  std::vector<int> v{};
  v.reserve(1000);

  while (input >> z)
  {
    for (int i : v)
    {
      for (int j : v)
      {
        if (i == j) continue;
        if (i + j + z == Y)
        {
          //std::cout << i * j * z << std::endl;
          return i * j * z;
        }
      }
    }
    v.emplace_back(z);
  }
  assert(false); // should never come here
  throw "error!";
}
