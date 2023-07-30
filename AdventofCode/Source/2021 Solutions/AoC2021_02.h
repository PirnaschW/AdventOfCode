template<> Number AoC<2021, 2, A>(std::istream& input)
{
  int z = 0;
  int x = 0;
  int y = 0;

  std::string s;
  while (input >> s >> z)
  {
    if (s == "forward") x += z;
    else if (s == "down") y += z;
    else if (s == "up") y -= z;
  }
  return x * y;
}

template<> Number AoC<2021, 2, B>(std::istream& input)
{
  int z = 0;
  int x = 0;
  int y = 0;
  int a = 0;

  std::string s;
  while (input >> s >> z)
  {
    if (s == "forward") { x += z; y += a * z; }
    else if (s == "down") a += z;
    else if (s == "up") a -= z;
  }
  return x * y;
}
