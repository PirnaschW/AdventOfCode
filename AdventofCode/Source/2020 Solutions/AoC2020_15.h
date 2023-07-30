template<> Number AoC<2020, 15, A>(std::istream& input)
{
  std::unordered_map<int, int> map{};   // number spoken (int 1) in round (int 2)
  int i{ 0 };
  int z{ 0 };
  while (input >> z)
  {
    int& r = map[z];
    r = ++i;
    char comma{};
    input >> comma;
  }

  int n{ 0 };
  for (++i; i < 2020; ++i)
  {
    int& r = map[n];
    if (r == 0) // never before spoken
    {
      r = i;
      n = 0;
    }
    else
    {
      n = i - r;
      r = i;
    }
  }

  return n;
}


template<> Number AoC<2020, 15, B>(std::istream& input)
{
  std::unordered_map<long long, long long> map{};   // number spoken (long long 1) in round (long long 2)
  long long i{ 0 };
  long long z{ 0 };
  while (input >> z)
  {
    long long& r = map[z];
    r = ++i;
    char comma{};
    input >> comma;
  }

  long long n{ 0 };
  for (++i; i < 30000000LL; ++i)
  {
    long long& r = map[n];
    if (r == 0) // never before spoken
    {
      r = i;
      n = 0;
    }
    else
    {
      n = i - r;
      r = i;
    }
  }

  return n;
}
