template<> Number AoC<2022, 15, A>(std::istream& input)
{

  struct pos
  {
    Number x;
    Number y;
  };

  struct sensor
  {
    pos location;
    pos nearestB;
    Number Mdistance;
  };

  struct H
  {
    static Number MDistance(const pos& p1, const pos& p2)
    {
      return abs(p1.x - p2.x) + abs(p1.y - p2.y);
    }
  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector



  std::vector<sensor> sensors{};
  sensors.reserve(v.size());
  for (const auto& line : v)
  {
    sensor s;
    size_t count = sscanf_s(line.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &s.location.x, &s.location.y, &s.nearestB.x, &s.nearestB.y);
    assert(count == 4);
    s.Mdistance = H::MDistance(s.nearestB,s.location);
    sensors.push_back(s);
  }

  Number xmin{ 1'000'000'000 };
  Number xmax{ -1'000'000'000 };

  for (auto i = 0; i < sensors.size(); ++i)
  {
    if (xmin > sensors[i].location.x - sensors[i].Mdistance) xmin = sensors[i].location.x - sensors[i].Mdistance;
    if (xmax < sensors[i].location.x + sensors[i].Mdistance) xmax = sensors[i].location.x + sensors[i].Mdistance;
  }


  pos p{ 0,2'000'000 };
  //p.y = 10;

  Number z{ 0 };
  for (p.x = xmin; p.x <= xmax; ++p.x)
  {
    bool nextx = false;
    for (auto i = 0; i < sensors.size(); ++i)
    {
      if (sensors[i].nearestB.x == p.x && sensors[i].nearestB.y == p.y)
      {
        nextx = true;
        break;
      }
    }
    if (!nextx)
    {
      for (auto i = 0; i < sensors.size(); ++i)
      {
        auto d = H::MDistance(p, sensors[i].location);
        if (d <= sensors[i].Mdistance)
        {
          ++z;
          break;
        }
      }
    }
  }

  return z;
}

template<> Number AoC<2022, 15, B>(std::istream& input)
{

  struct pos
  {
    Number x;
    Number y;
  };

  struct sensor
  {
    pos location;
    pos nearestB;
    Number Mdistance;
  };

  struct H
  {
    static Number MDistance(const pos& p1, const pos& p2)
    {
      return abs(p1.x - p2.x) + abs(p1.y - p2.y);
    }

    static bool Check(const std::vector<sensor>& sensors, const pos& p)
    {
      if (p.x < 0 || p.x > 4'000'000 || p.y < 0 || p.y > 4'000'000) return false;
      for (auto i = 0; i < sensors.size(); ++i)
      {
        auto d = H::MDistance(p, sensors[i].location);
        if (d <= sensors[i].Mdistance) return false;
      }
      return true;
    }

  };

  std::vector<std::string> v = ReadLines(input);                // read all lines into vector


  std::vector<sensor> sensors{};
  sensors.reserve(v.size());
  for (const auto& line : v)
  {
    sensor s;
    size_t count = sscanf_s(line.c_str(), "Sensor at x=%lld, y=%lld: closest beacon is at x=%lld, y=%lld", &s.location.x, &s.location.y, &s.nearestB.x, &s.nearestB.y);
    assert(count == 4);
    s.Mdistance = H::MDistance(s.nearestB, s.location);
    sensors.push_back(s);
  }

  pos p{};

  bool more{ true };
  for (auto i = 0; more && i < sensors.size(); ++i)
  {
    for (auto z = 0; z <= sensors[i].Mdistance+1; ++z)
    {
      p.x = sensors[i].location.x - z;
      p.y = sensors[i].location.y - sensors[i].Mdistance + z - 1;
      if (H::Check(sensors, p))
      {
        more = false;
        break;
      }
      p.x = sensors[i].location.x + z;
      p.y = sensors[i].location.y - sensors[i].Mdistance + z - 1;
      if (H::Check(sensors, p))
      {
        more = false;
        break;
      }

      p.x = sensors[i].location.x + z;
      p.y = sensors[i].location.y + sensors[i].Mdistance - z + 1;
      if (H::Check(sensors, p))
      {
        more = false;
        break;
      }

      p.x = sensors[i].location.x - z;
      p.y = sensors[i].location.y + sensors[i].Mdistance - z + 1;
      if (H::Check(sensors, p))
      {
        more = false;
        break;
      }
    }
  }

  return p.x * 4'000'000 + p.y;
}
