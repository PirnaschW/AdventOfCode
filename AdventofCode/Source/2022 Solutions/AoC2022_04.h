template<> Number AoC<2022, 4, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);
  Number z = 0;

  for (const auto& line : v)
  {
    std::istringstream str(line);

    Number min1 = 0;
    Number max1 = 0;
    Number min2 = 0;
    Number max2 = 0;
    char char1 = 0;
    char char2 = 0;
    char comma = 0;
    str >> min1 >> char1 >> max1 >> comma >> min2 >> char2 >> max2;

    if ((min1 >= min2 && max1 <= max2) ||
        (min2 >= min1 && max2 <= max1)) z++;
  }
  return z;
}

template<> Number AoC<2022, 4, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);
  Number z = 0;

  for (const auto& line : v)
  {
    std::istringstream str(line);

    Number min1 = 0;
    Number max1 = 0;
    Number min2 = 0;
    Number max2 = 0;
    char char1 = 0;
    char char2 = 0;
    char comma = 0;
    str >> min1 >> char1 >> max1 >> comma >> min2 >> char2 >> max2;

    if ((max2 >= min1 && min2 <= max1) ||
        (max1 >= min2 && min1 <= max2)) z++;
  }
  return z;
}

