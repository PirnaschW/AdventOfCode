//template<> auto InputData<2016, 15, A>() { return "Disc #1 has 5 positions; at time=0, it is at position 4.\nDisc #2 has 2 positions; at time=0, it is at position 1.\n";}; // Result: 5
template<> Number AoC<2016, 15, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  class Disc
  {
  public:
    int npos{ 0 };
    int pos0{ 0 };
  };

  std::vector<Disc> disc{};
  disc.resize(v.size());

  for (int i = 0; i < v.size(); ++i)
  {
    // Disc #1 has 13 positions; at time=0, it is at position 1.
    // Disc #2 has 19 positions; at time=0, it is at position 10.
    // Disc #3 has 3 positions; at time=0, it is at position 2.
    // Disc #4 has 7 positions; at time=0, it is at position 1.
    // Disc #5 has 5 positions; at time=0, it is at position 3.
    // Disc #6 has 17 positions; at time=0, it is at position 5.
    int n{ 0 };
    int z = sscanf_s(v[i].c_str(), "Disc #%d has %d positions; at time=0, it is at position %d.", &n, &disc[i].npos, &disc[i].pos0);
    assert(z == 3);
    assert(n == i + 1);
  }

  Number step{ 1 };
  int discindex{ 0 };
  Number t{ 0 };
  while (discindex < disc.size())
  {
    t += step;
    for (int i = discindex; i < disc.size(); ++i)
    {
      if ((disc[i].pos0 + t + i + 1) % disc[i].npos)
      {
        break;
      }
      else
      {
        step *= disc[i].npos;
        ++discindex;
      }
    }
  }

  return t;
}

//template<> auto InputData<2016, 15, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2016, 15, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  const Input v = ReadLines(input);  // read all lines into vector

  class Disc
  {
  public:
    int npos{ 0 };
    int pos0{ 0 };
  };

  std::vector<Disc> disc{};
  disc.resize(v.size()+1);
  disc[v.size()].npos = 11;
  disc[v.size()].pos0 = 0;

  for (int i = 0; i < v.size(); ++i)
  {
    // Disc #1 has 13 positions; at time=0, it is at position 1.
    // Disc #2 has 19 positions; at time=0, it is at position 10.
    // Disc #3 has 3 positions; at time=0, it is at position 2.
    // Disc #4 has 7 positions; at time=0, it is at position 1.
    // Disc #5 has 5 positions; at time=0, it is at position 3.
    // Disc #6 has 17 positions; at time=0, it is at position 5.
    int n{ 0 };
    int z = sscanf_s(v[i].c_str(), "Disc #%d has %d positions; at time=0, it is at position %d.", &n, &disc[i].npos, &disc[i].pos0);
    assert(z == 3);
    assert(n == i + 1);
  }

  Number step{ 1 };
  int discindex{ 0 };
  Number t{ 0 };
  while (discindex < disc.size())
  {
    t += step;
    for (int i = discindex; i < disc.size(); ++i)
    {
      if ((disc[i].pos0 + t + i + 1) % disc[i].npos)
      {
        break;
      }
      else
      {
        step *= disc[i].npos;
        ++discindex;
      }
    }
  }

  return t;
}
