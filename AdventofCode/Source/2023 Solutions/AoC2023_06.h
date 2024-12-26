//template<> auto InputData<2023, 6, A>() { return "Time:      7  15   30\nDistance:  9  40  200\n";}; // Result: 288
template<> Number AoC<2023, 6, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto ReadLine = [](const char* const line, std::vector<Number>& v)
    {
      int p{ 0 };
      int n{};
      Number z{};
      while (sscanf_s(line + p, "%lld%n", &z, &n) == 1)
      {
        p += n;
        v.push_back(z);
      }
    };

  assert(v.size() == 2);
  std::vector<Number> time{};
  std::vector<Number> dist{};
  ReadLine(v[0].c_str() + strlen("Time:"), time);
  ReadLine(v[1].c_str() + strlen("Distance:"), dist);
  assert(time.size() == dist.size());

  Number result{ 1 };
  for (size_t i = 0; i < time.size(); ++i)
  {
    Number z = time[i] * time[i] - 4 * dist[i];
    long double r = sqrtl(static_cast<long double>(z) * 0.25);
    Number rInt = static_cast<Number>(r);
    if (!(time[i] % 2) && rInt * rInt * 4 == z) --rInt;
    if (time[i] % 2) rInt = static_cast<Number>(r + 0.5);
    Number n = 2 * rInt + (time[i] % 2 ? 0 : 1);

    if (time[i] % 2)
    {
      Number tt = (time[i] + 1) / 2;
      assert((tt - rInt) * (time[i] - (tt - rInt)) > dist[i]);
      assert((tt - (rInt + 1)) * (time[i] - (tt - (rInt + 1))) <= dist[i]);
    }
    else
    {
      Number tt = time[i] / 2;
      assert((tt - rInt) * (time[i] - (tt - rInt)) > dist[i]);
      assert((tt - (rInt + 1)) * (time[i] - (tt - (rInt + 1))) <= dist[i]);
    }
    result *= n;
  }

  return result;
}

//template<> auto InputData<2023, 6, B>() { return "Time:      7  15   30\nDistance:  9  40  200\n";}; // Result: 71503
template<> Number AoC<2023, 6, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  auto ReadLine = [](const char* const line, std::vector<Number>& v)
    {
      int p{ 0 };
      int n{};
      Number z{};
      while (sscanf_s(line + p, "%lld%n", &z, &n) == 1)
      {
        p += n;
        v.push_back(z);
      }
    };

  assert(v.size() == 2);
  std::vector<Number> time{};
  std::vector<Number> dist{};
  std::erase(v[0], ' ');
  std::erase(v[1], ' ');
  ReadLine(v[0].c_str() + strlen("Time:"), time);
  ReadLine(v[1].c_str() + strlen("Distance:"), dist);
  assert(time.size() == dist.size());

  Number result{ 1 };
  for (size_t i = 0; i < time.size(); ++i)
  {
    Number z = time[i] * time[i] - 4 * dist[i];
    long double r = sqrtl(static_cast<long double>(z) * 0.25);
    Number rInt = static_cast<Number>(r);
    if (!(time[i] % 2) && rInt * rInt * 4 == z) --rInt;
    if (time[i] % 2) rInt = static_cast<Number>(r + 0.5);
    Number n = 2 * rInt + (time[i] % 2 ? 0 : 1);

    if (time[i] % 2)
    {
      Number tt = (time[i] + 1) / 2;
      assert((tt - rInt) * (time[i] - (tt - rInt)) > dist[i]);
      assert((tt - (rInt + 1)) * (time[i] - (tt - (rInt + 1))) <= dist[i]);
    }
    else
    {
      Number tt = time[i] / 2;
      assert((tt - rInt) * (time[i] - (tt - rInt)) > dist[i]);
      assert((tt - (rInt + 1)) * (time[i] - (tt - (rInt + 1))) <= dist[i]);
    }
    result *= n;
  }

  return result;
}
