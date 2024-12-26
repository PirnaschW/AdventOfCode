//template<> auto InputData<2023, 4, A>() { return
//"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
//"Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
//"Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
//"Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
//"Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
//"Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11\n";}; // Result: 13
template<> Number AoC<2023, 4, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int BufferSize{ 255U };
  assert(BufferSize > v[0].size());

  Number total{ 0 };
  for (size_t i = 0; i < v.size(); ++i)
  {
    int nr{ 0 };
    char buf1[BufferSize]{};
    char buf2[BufferSize]{};

    int z = sscanf_s(v[i].c_str(), "Card %d:%[^|]|%[^\n]", &nr, buf1, BufferSize - 1, buf2, BufferSize - 1);
    assert(z == 3);

    int p1{ 0 };
    int off1{ 0 };
    std::unordered_set<Number> win{};
    do
    {
      int num{ -1 };
      int z1 = sscanf_s(buf1 + p1, "%d%n", &num, &off1);
      if (z1 != 1) break;

      assert(off1 > 0);
      p1 += off1;
      assert(win.find(num) == win.cend());
      win.insert(num);
    } while (true);

    int p2{ 0 };
    int off2{ 0 };
    Number value{ 1 };
    do
    {
      int num{ -1 };
      int z2 = sscanf_s(buf2 + p2, "%d%n", &num, &off2);
      if (z2 != 1) break;

      assert(off2 > 0);
      p2 += off2;
      if (win.find(num) != win.cend())
      {
        value *= 2;
      }
    } while (true);

    value /= 2;
    total += value;
  }
  return total;
}

//template<> auto InputData<2023, 4, B>() { return
//"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n"
//"Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n"
//"Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n"
//"Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n"
//"Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n"
//"Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11\n";}; // Result: 30
template<> Number AoC<2023, 4, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  constexpr unsigned int BufferSize{ 255U };
  assert(BufferSize > v[0].size());

  std::vector<Number> count(v.size(),1);

  for (size_t i = 0; i < v.size(); ++i)
  {
    int nr{ 0 };
    char buf1[BufferSize]{};
    char buf2[BufferSize]{};

    int z = sscanf_s(v[i].c_str(), "Card %d:%[^|]|%[^\n]", &nr, buf1, BufferSize - 1, buf2, BufferSize - 1);
    assert(z == 3);

    int p1{ 0 };
    int off1{ 0 };
    std::unordered_set<Number> win{};
    do
    {
      int num{ -1 };
      int z1 = sscanf_s(buf1 + p1, "%d%n", &num, &off1);
      if (z1 != 1) break;

      assert(off1 > 0);
      p1 += off1;
      assert(win.find(num) == win.cend());
      win.insert(num);
    } while (true);

    int p2{ 0 };
    int off2{ 0 };
    Number wins{ 0 };
    do
    {
      int num{ -1 };
      int z2 = sscanf_s(buf2 + p2, "%d%n", &num, &off2);
      if (z2 != 1) break;

      assert(off2 > 0);
      p2 += off2;
      if (win.find(num) != win.cend())
      {
        ++wins;
      }
    } while (true);

    for (int j = 0; j < wins; ++j)
      count[i + j + 1] += count[i];
  }

  Number total{ 0 };
  for (size_t i = 0; i < count.size(); ++i)
  {
    total += count[i];
  }
  return total;
}
