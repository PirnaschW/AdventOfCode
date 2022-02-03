template<> Number AoC<2019, 2, A>(std::istream& input)
{

  struct H
  {
    static Number GetFuel(Number mass)
    {
      return mass > 6 ? mass / 3 - 2 : 0;
    }
  };

  auto v = ReadNumbers(input);
  Number z = 4;

  return z;
}

template<> Number AoC<2019, 2, B>(std::istream& input)
{
  struct H
  {
    static Number GetFuel(Number mass)
    {
      return mass > 6 ? mass / 3 - 2 : 0;
    }
  };


  auto v = ReadNumbers(input);
  Number z = 8;

  return z;
}
