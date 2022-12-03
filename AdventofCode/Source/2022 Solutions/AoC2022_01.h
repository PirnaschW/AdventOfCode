template<> Number AoC<2022, 1, A>(std::istream& input)
{
  Number max = 0;
  Number z = 0;
  std::vector<std::string> v = ReadLines(input);
  for (const auto& line : v)
  {
    if (line == "")
    {
      if (z > max) max = z;
      z = 0;
    }
    else
    {
      Number i = 0;
      std::istringstream str(line);
      str >> i;
      z += i;
    }
  }
  return max;
}

template<> Number AoC<2022, 1, B>(std::istream& input)
{
  std::vector<Number> max{};
  Number z = 0;
  std::vector<std::string> v = ReadLines(input);
  for (const auto& line : v)
  {
    if (line == "")
    {
      max.push_back(z);
      z = 0;
    }
    else
    {
      Number i = 0;
      std::istringstream str(line);
      str >> i;
      z += i;
    }
  }
  std::sort(max.begin(), max.end(), std::greater<Number>());
  return max[0]+max[1]+max[2];
}

