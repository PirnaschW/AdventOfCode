//template<> auto InputData<2015, 20, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 20, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int target{ 0 };
  int n = sscanf_s(v[0].c_str(), "%d", &target);
  assert(n == 1);
  target /= 10; // 3'310'000

  // sum all divisors (once)
  auto SumAllDivisors = [](int n) -> int
    {
      int sum{ n + 1 };
      for (int i = 2; i * i <= n; ++i)
      {
        if (n % i == 0)
        {
          sum += i;
          if (i * i != n)
            sum += n / i;
        }
      }
      return sum;
    };

  for (int i = target / 5; ; ++i)
  {
    int z = SumAllDivisors(i);
//    std::cout << i << ':' << z << std::endl;
    if (z >= target) return i;
  }
  return 0;
}

//template<> auto InputData<2015, 20, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 20, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int target{ 0 };
  int n = sscanf_s(v[0].c_str(), "%d", &target);
  assert(n == 1);
  target /= 11; // 3'009'091

  // sum all divisors (once)
  auto SumAllDivisors = [](int n) -> int
    {
      int sum{ 0 };
      for (int i = 1; i * i <= n; ++i)
      {
        if (n % i == 0)
        {
          if (n / i <= 50)
            sum += i;
          if (i <= 50 && i * i != n)
            sum += n / i;
        }
      }
      return sum;
    };

  for (int i = target / 5; ; ++i)
  {
    int z = SumAllDivisors(i);
    //std::cout << i << ':' << z << std::endl;
    if (z >= target) return i;
  }

  return 0;
}
