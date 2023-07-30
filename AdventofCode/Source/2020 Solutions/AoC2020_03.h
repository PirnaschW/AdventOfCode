template<> Number AoC<2020, 03, B>(std::istream& input)
{
  int x1{ 0 };
  int x2{ 0 };
  int x3{ 0 };
  int x4{ 0 };
  int x5{ 0 };
  int dx1{ 1 };
  int dx2{ 3 };
  int dx3{ 5 };
  int dx4{ 7 };
  int dx5{ 1 };
  long long n1{ 0 };
  long long n2{ 0 };
  long long n3{ 0 };
  long long n4{ 0 };
  long long n5{ 0 };
  std::string s{};
  bool check5{ true };
  while (input >> s && s.size() > 0)
  {
    if (s[x1] == '#') ++n1;
    if (s[x2] == '#') ++n2;
    if (s[x3] == '#') ++n3;
    if (s[x4] == '#') ++n4;
    if (s[x5] == '#') if (check5) ++n5;
    x1 += dx1;
    x2 += dx2;
    x3 += dx3;
    x4 += dx4;
    if (check5) {
      x5 += dx5;
    }
    check5 = !check5;

    x1 %= s.size();
    x2 %= s.size();
    x3 %= s.size();
    x4 %= s.size();
    x5 %= s.size();
  }
  long long n = n1 * n2 * n3 * n4 * n5;
  //std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << std::endl;
  return n;
}

template<> Number AoC<2020, 03, A>(std::istream& input)
{
  int x{ 0 };
  int dx{ 3 };
  int n{ 0 };
  std::string s{};
  while (input >> s && s.size() > 0)
  {
    if (s[x] == '#') ++n;
    x += dx;
    x %= s.size();
  }
  return n;
}

