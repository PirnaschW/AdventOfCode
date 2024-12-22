//template<> auto InputData<2016, 3, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 3, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int n{ 0 };

  for (const auto& line : v)
  {
    int a{ 0 };
    int b{ 0 };
    int c{ 0 };
    int z = sscanf_s(line.c_str(), "%d %d %d", &a, &b, &c);
    assert(z == 3);

    if (a + b > c && a + c > b && b + c > a) ++n;
  }

  return n;
}

//template<> auto InputData<2016, 3, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 3, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  int n{ 0 };

  auto Valid = [](int a, int b, int c) -> bool { return a + b > c && a + c > b && b + c > a; };

  for (int i=0; i<v.size(); i+=3)
  {
    int a1{ 0 };
    int b1{ 0 };
    int c1{ 0 };
    int a2{ 0 };
    int b2{ 0 };
    int c2{ 0 };
    int a3{ 0 };
    int b3{ 0 };
    int c3{ 0 };
    // 101 301 501
    // 102 302 502
    // 103 303 503
    int z1 = sscanf_s(v[i].c_str(), "%d %d %d", &a1, &a2, &a3);
    assert(z1 == 3);
    int z2 = sscanf_s(v[i+1].c_str(), "%d %d %d", &b1, &b2, &b3);
    assert(z2 == 3);
    int z3 = sscanf_s(v[i+2].c_str(), "%d %d %d", &c1, &c2, &c3);
    assert(z3 == 3);

    if (Valid(a1,b1,c1)) ++n;
    if (Valid(a2,b2,c2)) ++n;
    if (Valid(a3,b3,c3)) ++n;
  }

  // 1599 is too high
  return n;
}
