//template<> auto InputData<2023, 5, A>() { return
//"seeds: 79 14 55 13\n"
//"\n"
//"seed-to-soil map:\n"
//"50 98 2\n"
//"52 50 48\n"
//"\n"
//"soil-to-fertilizer map:\n"
//"0 15 37\n"
//"37 52 2\n"
//"39 0 15\n"
//"\n"
//"fertilizer-to-water map:\n"
//"49 53 8\n"
//"0 11 42\n"
//"42 0 7\n"
//"57 7 4\n"
//"\n"
//"water-to-light map:\n"
//"88 18 7\n"
//"18 25 70\n"
//"\n"
//"light-to-temperature map:\n"
//"45 77 23\n"
//"81 45 19\n"
//"68 64 13\n"
//"\n"
//"temperature-to-humidity map:\n"
//"0 69 1\n"
//"1 0 69\n"
//"\n"
//"humidity-to-location map:\n"
//"60 56 37\n"
//"56 93 4\n";}; // Result: 35
template<> Number AoC<2023, 5, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Map
  {
  public:
    void Append(const std::string& line)
    {
      Number t{ 0 };
      Number s{ 0 };
      Number c{ 0 };
      int z = sscanf_s(line.c_str(), "%lld %lld %lld", &t, &s, &c);
      assert(z == 3);
      part.push_back(Part(t, s, c));
    }
    Number GetMapped(Number in) const
    {
      for (size_t i = 0; i < part.size(); ++i)
      {
        if ((in >= part[i].source) && (in < part[i].source + part[i].count))
        {
          Number out = part[i].target + in - part[i].source;
          return out;
        }
      }
      return in;
    }

  private:
    class Part
    {
    public:
      Number target{};
      Number source{};
      Number count{};
    };

  private:
    std::vector<Part> part{};
  };

  auto ReadMap = [&v](size_t& line) -> Map
    {
      Map m{};
      ++line; // skip the title line
      while (++line < v.size() && v[line].size() > 0)
      {
        m.Append(v[line]);
      }
      return m;
    };


  constexpr int seedslen{ 6 };
  assert(v[0].substr(0, seedslen) == "seeds:");
  Number s{ 0 };
  int n{ 0 };
  int p{ seedslen };
  std::vector<Number> seed{};
  while (sscanf_s(v[0].c_str() + p, "%lld%n", &s, &n) == 1)
  {
    seed.push_back(s);
    p += n;
  }

  size_t line{ 1 };
  assert(v.size() > line);
  assert(v[line].size() == 0);
  constexpr size_t MapCount{ 7 };
  std::vector<Map> map{};
  for (size_t i=0; i<MapCount; ++i)
    map.push_back(ReadMap(line));

  auto Convert = [&map](Number in) -> Number
    {
      Number out{ in };
      for (size_t i = 0; i < map.size(); ++i)
        out = map[i].GetMapped(out);
      return out;
    };

  std::vector<Number> loc{};
  for (size_t i = 0; i < seed.size(); ++i)
    loc.push_back(Convert(seed[i]));

  std::sort(loc.begin(),loc.end());

  return loc[0];
}

//template<> auto InputData<2023, 5, B>() { return
//"seeds: 79 14 55 13\n"
//"\n"
//"seed-to-soil map:\n"
//"50 98 2\n"
//"52 50 48\n"
//"\n"
//"soil-to-fertilizer map:\n"
//"0 15 37\n"
//"37 52 2\n"
//"39 0 15\n"
//"\n"
//"fertilizer-to-water map:\n"
//"49 53 8\n"
//"0 11 42\n"
//"42 0 7\n"
//"57 7 4\n"
//"\n"
//"water-to-light map:\n"
//"88 18 7\n"
//"18 25 70\n"
//"\n"
//"light-to-temperature map:\n"
//"45 77 23\n"
//"81 45 19\n"
//"68 64 13\n"
//"\n"
//"temperature-to-humidity map:\n"
//"0 69 1\n"
//"1 0 69\n"
//"\n"
//"humidity-to-location map:\n"
//"60 56 37\n"
//"56 93 4\n";}; // Result: 35
template<> Number AoC<2023, 5, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  class Segment
  {
  public:
    Number start{};
    Number count{};
  };

  class Part
  {
  public:
    Segment segment{};
    Number offset{};
  };

  class Map
  {
  public:
    void Append(const std::string& line)
    {
      Number t{ 0 };
      Number s{ 0 };
      Number c{ 0 };
      int z = sscanf_s(line.c_str(), "%lld %lld %lld", &t, &s, &c);
      assert(z == 3);
      part.push_back(Part{ { s, c }, t - s });
    }
    void AppendUnmapped()
    {
      part.push_back(Part{ { 0, (std::numeric_limits<Number>::max)() }, 0 });  // adds a dummy mapping for all the rest
    }
    std::vector<Segment> MapSegments(const std::vector<Segment>& seg) const
    {
      std::vector<Segment> target{};
      for (const Segment& s : seg)
      {
        for (const Part& p : part)                                                                                     // map:           [.......]
        {
          if (s.start + s.count <= p.segment.start) continue;                                                          // case 1: [...]
          if (s.start >= p.segment.start + p.segment.count) continue;                                                  // case 5:                   [...]
          if (s.start >= p.segment.start && s.start + s.count <= p.segment.start + p.segment.count)                    // case 3           [...]
          {
            Segment inside{};
            inside.start = s.start + p.offset;  // map it
            inside.count = s.count;
            target.push_back(inside);
            break;
          }
          if (s.start < p.segment.start && s.start + s.count > p.segment.start)                                        // case 2      [.....
          {
            Number outside = p.segment.start - s.start;
            std::vector<Segment> remainder{};
            remainder.emplace_back(s.start, outside);
            std::vector<Segment> r = MapSegments(remainder);
            target.append_range(r);

            remainder.clear();
            remainder.emplace_back(p.segment.start, s.count - outside);
            r = MapSegments(remainder);
            target.append_range(r);
            break;
          }
          if (s.start < p.segment.start + p.segment.count && s.start + s.count > p.segment.start + p.segment.count)    // case 4              .......]
          {
            assert(s.start >= p.segment.start);  // if not, it should have been treated before
            Number outside = s.start + s.count - p.segment.start - p.segment.count;
            std::vector<Segment> remainder{};
            remainder.emplace_back(p.segment.start + p.segment.count, outside);
            std::vector<Segment> r = MapSegments(remainder);
            target.append_range(r);

            remainder.clear();
            remainder.emplace_back(s.start, s.count - outside);
            r = MapSegments(remainder);
            target.append_range(r);
            break;
          }
        }
      }
      return target;
    }

  private:
    std::vector<Part> part{};
  };

  auto ReadMap = [&v](size_t& line) -> Map
    {
      Map m{};
      ++line; // skip the title line
      while (++line < v.size() && v[line].size() > 0)
      {
        m.Append(v[line]);
      }
      m.AppendUnmapped();
      return m;
    };


  constexpr int seedslen{ 6 };
  assert(v[0].substr(0, seedslen) == "seeds:");
  Number s{ 0 };
  Number c{ 0 };
  int n{ 0 };
  int p{ seedslen };
  std::vector<Segment> seed{};
  while (sscanf_s(v[0].c_str() + p, "%lld%lld%n", &s, &c, &n) == 2)
  {
    seed.push_back({ s, c });
    p += n;
  }

  size_t line{ 1 };
  assert(v.size() > line);
  assert(v[line].size() == 0);
  constexpr size_t MapCount{ 7 };
  std::vector<Map> map{};
  for (size_t i = 0; i < MapCount; ++i)
    map.push_back(ReadMap(line));

  std::vector<Segment> current = seed;
  for (size_t i = 0; i < map.size(); ++i)
  {
    std::vector<Segment> result = map[i].MapSegments(current);
    current = result;
  }

  Number minLoc{ (std::numeric_limits<Number>::max)() };
  for (const Segment& s : current)
  {
    if (s.start < minLoc) minLoc = s.start;
  }

  return minLoc;
}

// works, but too slow:
//template<> Number AoC<2023, 5, B>(std::istream& input)
//{
//  using Input = std::vector<std::string>;
//  Input v = ReadLines(input);  // read all lines into vector
//
//  class Map
//  {
//  public:
//    void Append(const std::string& line)
//    {
//      Number t{ 0 };
//      Number s{ 0 };
//      Number c{ 0 };
//      int z = sscanf_s(line.c_str(), "%lld %lld %lld", &t, &s, &c);
//      assert(z == 3);
//      part.push_back(Part(t, s, c));
//    }
//    Number GetMapped(Number in) const
//    {
//      for (size_t i = 0; i < part.size(); ++i)
//      {
//        if ((in >= part[i].source) && (in < part[i].source + part[i].count))
//        {
//          Number out = part[i].target + in - part[i].source;
//          return out;
//        }
//      }
//      return in;
//    }
//
//  private:
//    class Part
//    {
//    public:
//      Number target{};
//      Number source{};
//      Number count{};
//    };
//
//  private:
//    std::vector<Part> part{};
//  };
//
//  auto ReadMap = [&v](size_t& line) -> Map
//    {
//      Map m{};
//      ++line; // skip the title line
//      while (++line < v.size() && v[line].size() > 0)
//      {
//        m.Append(v[line]);
//      }
//      return m;
//    };
//
//
//  constexpr int seedslen{ 6 };
//  assert(v[0].substr(0, seedslen) == "seeds:");
//  Number s{ 0 };
//  Number c{ 0 };
//  int n{ 0 };
//  int p{ seedslen };
//  std::vector<std::pair<Number, Number>> seed{};
//  while (sscanf_s(v[0].c_str() + p, "%lld%lld%n", &s, &c, &n) == 2)
//  {
//    seed.push_back(std::pair<Number, Number>(s, c));
//    p += n;
//  }
//
//  size_t line{ 1 };
//  assert(v.size() > line);
//  assert(v[line].size() == 0);
//  constexpr size_t MapCount{ 7 };
//  std::vector<Map> map{};
//  for (size_t i = 0; i < MapCount; ++i)
//    map.push_back(ReadMap(line));
//
//  auto Convert = [&map](Number in) -> Number
//    {
//      Number out{ in };
//      for (size_t i = 0; i < map.size(); ++i)
//        out = map[i].GetMapped(out);
//      return out;
//    };
//
//  Number minLoc{ (std::numeric_limits<Number>::max)() };
//  for (size_t i = 0; i < seed.size(); ++i)
//  {
//    for (Number j = 0; j < seed[i].second; ++j)
//    {
//      Number loc = Convert(seed[i].first + j);
//      if (loc < minLoc) minLoc = loc;
//    }
//  }
//
//  return minLoc;
//}
