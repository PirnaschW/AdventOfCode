//template<> auto InputData<2015, 16, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 16, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // children: 3
  // cats: 7
  // samoyeds: 2
  // pomeranians: 3
  // akitas: 0
  // vizslas: 0
  // goldfish: 5
  // trees: 3
  // cars: 2
  // perfumes: 1
  auto CanStillMatch = [](const std::string& thing, const Number& count) -> bool
    {
      if (thing == "children"    && count == 3) return true;
      if (thing == "cats"        && count == 7) return true;
      if (thing == "samoyeds"    && count == 2) return true;
      if (thing == "pomeranians" && count == 3) return true;
      if (thing == "akitas"      && count == 0) return true;
      if (thing == "vizslas"     && count == 0) return true;
      if (thing == "goldfish"    && count == 5) return true;
      if (thing == "trees"       && count == 3) return true;
      if (thing == "cars"        && count == 2) return true;
      if (thing == "perfumes"    && count == 1) return true;
      return false;
    };

  constexpr unsigned int BufSize{ 256 };
  for (const auto& line : v)
  {
    Number n{};
    char rest[BufSize]{};
    // Sue 1: children: 1, cars: 8, vizslas: 7
    int z = sscanf_s(line.c_str(), "Sue %lld: %[^\n]", &n, rest, BufSize);
    assert(z == 2);

    char* data = rest;
    while (data[0] != '\0')
    {
      char thing[BufSize]{};
      Number count{};
      Number offset{};
      int z1 = sscanf_s(data, " %[^:]:%lld%lln", thing, BufSize, &count, &offset);
      assert(z1 == 2);

      if (!CanStillMatch(thing, count)) break;
      data += offset;
      if (data[0] == ',') ++data;
    }
    if (data[0] == '\0') return n;
  }
  return -1;
}

//template<> auto InputData<2015, 16, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 16, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  // children: 3
  // cats: 7
  // samoyeds: 2
  // pomeranians: 3
  // akitas: 0
  // vizslas: 0
  // goldfish: 5
  // trees: 3
  // cars: 2
  // perfumes: 1
  auto CanStillMatch = [](const std::string& thing, const Number& count) -> bool
    {
      if (thing == "cats"        && count > 7) return true;
      if (thing == "trees"       && count > 3) return true;

      if (thing == "pomeranians" && count < 3) return true;
      if (thing == "goldfish"    && count < 5) return true;

      if (thing == "children"    && count == 3) return true;
      if (thing == "samoyeds"    && count == 2) return true;
      if (thing == "akitas"      && count == 0) return true;
      if (thing == "vizslas"     && count == 0) return true;
      if (thing == "cars"        && count == 2) return true;
      if (thing == "perfumes"    && count == 1) return true;
      return false;
    };

  constexpr unsigned int BufSize{ 256 };
  for (const auto& line : v)
  {
    Number n{};
    char rest[BufSize]{};
    // Sue 1: children: 1, cars: 8, vizslas: 7
    int z = sscanf_s(line.c_str(), "Sue %lld: %[^\n]", &n, rest, BufSize);
    assert(z == 2);

    char* data = rest;
    while (data[0] != '\0')
    {
      char thing[BufSize]{};
      Number count{};
      Number offset{};
      int z1 = sscanf_s(data, " %[^:]:%lld%lln", thing, BufSize, &count, &offset);
      assert(z1 == 2);

      if (!CanStillMatch(thing, count)) break;
      data += offset;
      if (data[0] == ',') ++data;
    }
    if (data[0] == '\0') return n;
  }
  return -1;
}
