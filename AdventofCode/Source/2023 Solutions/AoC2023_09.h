//template<> auto InputData<2023, 9, A>() { return "0 3 6 9 12 15\n1 3 6 10 15 21\n10 13 16 21 30 45\n";}; // Result: 114
template<> Number AoC<2023, 9, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number res{ 0 };
  for (const auto& line : v)
  {
    std::vector<Number> h{};
    Number z{};
    std::stringstream str(line);
    while (str >> z) { h.emplace_back(z); }

    auto Diff = [](const std::vector<Number>& h)->std::vector<Number>
      {
        std::vector<Number> res{};
        for (size_t i = 1; i < h.size(); ++i)
          res.push_back(h[i] - h[i - 1]);
        return res;
      };

    auto IsAllZeroes = [](const std::vector<Number>& h)->bool {for (size_t i = 0; i < h.size(); ++i) if (h[i] != 0) return false; return true; };
    auto Reduce = [&IsAllZeroes,&Diff](const std::vector<Number>& h, auto &Reduce)->Number
      {
        std::vector<Number> hh = Diff(h);
        if (IsAllZeroes(hh)) return h.back();
        else return Reduce(hh,Reduce) + h.back();
      };

    res += Reduce(h,Reduce);
  }
  return res;
}

//template<> auto InputData<2023, 9, B>() { return "0 3 6 9 12 15\n1 3 6 10 15 21\n10 13 16 21 30 45\n";}; // Result: 2
template<> Number AoC<2023, 9, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  Number res{ 0 };
  for (const auto& line : v)
  {
    std::vector<Number> h{};
    Number z{};
    std::stringstream str(line);
    while (str >> z) { h.emplace_back(z); }

    auto Diff = [](const std::vector<Number>& h)->std::vector<Number>
      {
        std::vector<Number> res{};
        for (size_t i = 1; i < h.size(); ++i)
          res.push_back(h[i] - h[i - 1]);
        return res;
      };

    auto IsAllZeroes = [](const std::vector<Number>& h)->bool {for (size_t i = 0; i < h.size(); ++i) if (h[i] != 0) return false; return true; };
    auto Reduce = [&IsAllZeroes,&Diff](const std::vector<Number>& h, auto &Reduce)->Number
      {
        std::vector<Number> hh = Diff(h);
        if (IsAllZeroes(hh)) return h.front();
        else return h.front() - Reduce(hh,Reduce);
      };

    res += Reduce(h,Reduce);
  }
  return res;
}
