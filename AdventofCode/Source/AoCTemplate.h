template<> Number AoC<2022, XX, A>(std::istream& input)
{
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



  int z{ 0 };
  return z;
}

template<> Number AoC<2022, XX, B>(std::istream& input)
{
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



  int z{ 0 };
  return z;
}
