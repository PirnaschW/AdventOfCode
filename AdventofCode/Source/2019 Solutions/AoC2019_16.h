//template<> auto InputData<2019, 16, A>() { return "12345678\n4\n"; };  // 01029498
//template<> auto InputData<2019, 16, A>() { return "80871224585914546619083218645595\n100\n"; };  // 24176176
//template<> auto InputData<2019, 16, A>() { return "19617804207202209144916044189917\n100\n"; };  // 73745418
//template<> auto InputData<2019, 16, A>() { return "69317163492948606335995924319873\n100\n"; };  // 52432133
template<> Number AoC<2019, 16, A>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);  // read all lines into vector

  Number phases = 100;
  if (v.size() == 2)  // test case
  {
    std::stringstream s(v[1]);
    s >> phases;
  }

  constexpr int patternLength = 4;
  constexpr std::array<int,patternLength> pattern{ 0,1,0,-1 };
  std::string signal{ v[0] };
  for (int i = 0; i < signal.size(); ++i) signal[i] -= 48;

  for (Number n = 0; n < phases; ++n)
  {
    std::string newsignal(signal.size(), '\0');
    for (int outdigit = 0; outdigit < signal.size(); ++outdigit)
    {
      int z{ 0 };
      for (int indigit = 0; indigit < signal.size(); ++indigit)
      {
        const int p = pattern[((indigit + 1) / (outdigit + 1)) % patternLength];
        z += p * signal[indigit];
      }
      newsignal[outdigit] = (z > 0 ? z : -z) % 10;
    }
    std::swap(signal, newsignal);
  }

  for (int i = 0; i < 8; ++i) signal[i] += 48;
  throw signal.substr(0, 8);
}


//template<> auto InputData<2019, 16, B>() { return "167 ORE => 5 NZVS\n165 ORE => 6 DCFZ\n12 HKGWZ, 1 GPVTF, 8 PSHF => 9 QDVJ\n"; }; // 
template<> Number AoC<2019, 16, B>(std::istream& input)
{
  std::vector<std::string> v = ReadLines(input);  // read all lines into vector

  Number phases = 100;
  if (v.size() == 2)  // test case
  {
    std::stringstream s(v[1]);
    s >> phases;
  }

  constexpr int patternLength = 4;
  constexpr std::array<int,patternLength> pattern{ 0,1,0,-1 };

  for (int i = 0; i < v[0].size(); ++i) v[0][i] -= 48;

  int startat{ 0 };
  for (int i = 0; i < 7; ++i)
  {
    startat *= 10;
    startat += v[0][i];
  }

  size_t length = 10000 * v[0].size() - startat;
  std::string signal{};
  signal.reserve(length);
  signal.append(v[0].substr(startat % v[0].size()));

  Number repeat = length / v[0].size();
  for (Number n = 0; n < repeat; ++n)
  {
    signal.append(v[0]);
  }
  assert(signal.size() == length);

  for (Number n = 0; n < phases; ++n)
  {
    std::string newsignal(signal.size(), '\0');

    char z{ 0 };
    for (Number outdigit = startat + signal.size() - 1; outdigit >= startat; --outdigit)
    {
      z += signal[outdigit - startat];
      z %= 10;
      newsignal[outdigit - startat] = z;
    }
    std::swap(signal, newsignal);
  }

  for (int i = 0; i < 8; ++i) signal[i] += 48;
  throw signal.substr(0, 8);
}
