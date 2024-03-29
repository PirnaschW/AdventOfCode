template<> Number AoC<2019, 1, A>(std::istream& input)
{

  struct H
  {
    static Number GetFuel(Number mass)
    {
      return mass > 6 ? mass / 3 - 2 : 0;
    }
  };


  auto v = ReadNumbers(input);
  Number z = 0;

  for (auto m : v) z += H::GetFuel(m);
  return z;
}

template<> Number AoC<2019, 1, B>(std::istream& input)
{

  struct H
  {
    static Number GetFuel(Number mass)
    {
      return mass > 6 ? mass / 3 - 2 : 0;
    }
    static Number GetFuelFuel(Number mass)
    {
      Number z{ 0 };
      Number zz{ mass };
      while ((zz = GetFuel(zz)) != 0) z += zz;
      return z;
    }
  };


  auto v = ReadNumbers(input);
  Number z = 0;

  for (auto m : v) z += H::GetFuelFuel(m);
  return z;
}
