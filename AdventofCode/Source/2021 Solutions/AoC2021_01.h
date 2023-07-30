template<> Number AoC<2021, 1, A>(std::istream& input)
{
  int z = std::numeric_limits<int>::max();
  int p = z;
  int n = 0;
  while (input >> z)
  {
    if (z > p) ++n;
    p = z;
  }

  return n;
}

template<> Number AoC<2021, 1, B>(std::istream& input)
{
  int z = std::numeric_limits<int>::max();
  int p1 = z;
  int p2 = z;
  int p3 = z;
  int n = 0;
  while (input >> z)
  {
    if (z > p3) ++n;
    p3 = p2;
    p2 = p1;
    p1 = z;
  }
  return n;
}

