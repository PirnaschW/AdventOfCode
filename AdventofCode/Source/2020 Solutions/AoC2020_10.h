void AoC2020_10A(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector <int> a{};
  a.reserve(v.size() + 2);

  a.emplace_back(0);
  for (const auto& vv : v) a.emplace_back(std::stoi(vv));
  std::sort(a.begin(), a.end());
  a.emplace_back(a[a.size() - 1] + 3);

  int n1{ 0 };
  int n3{ 0 };
  for (int i = 1; i < a.size(); ++i)
  {
    assert(a[i] - a[i - 1] < 4);
    switch (a[i] - a[i - 1])
    {
      case 1: ++n1; break;
      case 3: ++n3; break;
      default: break;
    }
  }

  std::cout << n1 * n3 << std::endl;
}

long long ss(long long s) { return s * (s - 1) / 2 + 1; }

void AoC2020_10B(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);                // read all lines into vector

  std::vector <int> a{};
  a.reserve(v.size() + 2);

  a.emplace_back(0);
  for (const auto& vv : v) a.emplace_back(std::stoi(vv));
  std::sort(a.begin(), a.end());
  a.emplace_back(a[a.size() - 1] + 3);

  long long z{ 1 };
  long long s{ 0 };
  for (int i = 1; i < a.size(); ++i)
  {
    assert(a[i] - a[i - 1] < 4);
    switch (a[i] - a[i - 1])
    {
      case 0: break;
      case 1: ++s; break;
      case 2: break;
      case 3: z *= ss(s); s = 0;  break;
      default: break;
    }
  }

  std::cout << z << std::endl;
}
