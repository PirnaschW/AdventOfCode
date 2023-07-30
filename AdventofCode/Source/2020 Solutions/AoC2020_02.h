template<> Number AoC<2020, 2, B>(std::istream& input)
{
  int n1{ 0 };
  int n2{ 0 };
  char minus{ 0 };
  char colon{ 0 };
  char c{ 0 };
  std::string s;
  int z{ 0 };

  while (input >> n1 >> minus >> n2 >> c >> colon >> s)
  {
    assert(minus == '-' && colon == ':');

    if ((s[n1 - 1] == c) != (s[n2 - 1] == c)) ++z; // password valid
  }

  return z;
}

template<> Number AoC<2020, 2, A>(std::istream& input)
{
  int n1{ 0 };
  int n2{ 0 };
  char minus{ 0 };
  char colon{ 0 };
  char c{ 0 };
  std::string s;
  int z{ 0 };

  while (input >> n1 >> minus >> n2 >> c >> colon >> s)
  {
    assert(minus == '-' && colon == ':');
    int n{ 0 };
    for (char a : s) if (a == c) ++n; // count matches
    if (n >= n1 && n <= n2) ++z; // password valid
  }

  return z;
}
