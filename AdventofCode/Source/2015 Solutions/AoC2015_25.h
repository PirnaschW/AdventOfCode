//template<> auto InputData<2015, 25, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 25, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // To continue, please consult the code grid in the manual.  Enter the code at row 2978, column 3083.

  Number c{ 0 };
  Number r{ 0 };
  int z = sscanf_s(v[0].c_str(), "To continue, please consult the code grid in the manual.  Enter the code at row %lld, column %lld.", &r, &c);
  assert(z == 2);

  const Number count = (c + r - 1) * (c + r) / 2 - r;   // (COLUMN()+ROW()-1)*(COLUMN()+ROW())/2-ROW()+1

  Number code = 20151125;
  for (int i = 0; i < count; ++i)
  {
    code *= 252533;
    code %= 33554393;
  }
  return code;
}

//template<> auto InputData<2015, 25, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 25, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector
  return 0;
}
