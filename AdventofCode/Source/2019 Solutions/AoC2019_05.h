template<> Number AoC<2019, 5, A>(std::istream& input)
{
  auto v = ReadNumbers(input, ',');

  struct H
  {
    static int f(void)
    {
    }
  };


  std::string line{};
  getline(input, line);
  std::istringstream str(line);



  int z{ 51 };
  return z;
}

template<> Number AoC<2019, 5, B>(std::istream& input)
{
  //auto v = ReadWords(input, '-');

  struct H
  {
    static int f(void)
    {
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector
//std::vector<std::string> v = ReadWords()                 // read all words into vector 
//std::vector<std::vector<std::string>> v = ReadGroups();  // read all lines, grouping multiple lines separated by blank lines into sub-vector 

  std::string line{};
  getline(input, line);
  std::istringstream str(line);



  int z{ 52 };
  return z;
}
