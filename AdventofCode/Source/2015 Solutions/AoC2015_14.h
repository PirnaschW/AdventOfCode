//template<> auto InputData<2015, 14, A>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 14, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  class Reindeer
  {
  public:
    Reindeer() = delete;
    Reindeer(const std::string& name, Number speed, Number duration, Number pause) noexcept : name_(name), speed_(speed), duration_(duration), pause_(pause) {}

    Number GetDistanceAt(Number time) const noexcept
    {
      Number completeCycles = time / (duration_ + pause_);
      Number extraFlytime = time % (duration_ + pause_);
      if (extraFlytime > duration_) extraFlytime = duration_;
      return speed_ * (duration_ * completeCycles + extraFlytime);
    }
  private:
    const std::string name_;
    const Number speed_;
    const Number duration_;
    const Number pause_;
  };
  using Reindeers = std::vector<Reindeer>;

  Reindeers reindeers{};
  constexpr unsigned int BufSize{ 33 };
  for (const auto& line : v)
  {
    char name[BufSize]{};
    Number speed{};
    Number duration{};
    Number pause{};
    // Rudolph can fly 22 km/s for 8 seconds, but then must rest for 165 seconds.
    int z = sscanf_s(line.c_str(), "%s can fly %lld km/s for %lld seconds, but then must rest for %lld seconds.", name, BufSize, &speed, &duration, &pause);
    assert(z == 4);
    reindeers.emplace_back(name, speed, duration, pause);
  }

  constexpr Number time{ 2503 };
  Number maxdistanceTravelled{ 0 };
  for (const auto& reindeer : reindeers)
  {
    Number distanceTravelled = reindeer.GetDistanceAt(time);
    if (distanceTravelled > maxdistanceTravelled) maxdistanceTravelled = distanceTravelled;
  }

  return maxdistanceTravelled;
}

//template<> auto InputData<2015, 14, B>() { return "Testdata\n";}; // Result: ?
template<> Number AoC<2015, 14, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector


  class Reindeer
  {
  public:
    Reindeer() = delete;
    Reindeer(const std::string& name, Number speed, Number duration, Number pause) noexcept : name_(name), speed_(speed), duration_(duration), pause_(pause) {}

    Number GetDistanceAt(Number time) const noexcept
    {
      Number completeCycles = time / (duration_ + pause_);
      Number extraFlytime = time % (duration_ + pause_);
      if (extraFlytime > duration_) extraFlytime = duration_;
      return speed_ * (duration_ * completeCycles + extraFlytime);
    }
  private:
    const std::string name_;
    const Number speed_;
    const Number duration_;
    const Number pause_;
  };
  using Reindeers = std::vector<Reindeer>;

  Reindeers reindeers{};
  constexpr unsigned int BufSize{ 33 };
  for (const auto& line : v)
  {
    char name[BufSize]{};
    Number speed{};
    Number duration{};
    Number pause{};
    // Rudolph can fly 22 km/s for 8 seconds, but then must rest for 165 seconds.
    int z = sscanf_s(line.c_str(), "%s can fly %lld km/s for %lld seconds, but then must rest for %lld seconds.", name, BufSize, &speed, &duration, &pause);
    assert(z == 4);
    reindeers.emplace_back(name, speed, duration, pause);
  }

  constexpr Number time{ 2503 };
  std::vector<Number> points{};
  points.resize(reindeers.size());
  for (auto i = 0; i < reindeers.size(); ++i)
  {
    points[i] = 0;
  }

  for (Number t = 1; t <= time; ++t)
  {
    Number maxd{ -1 };
    Number maxi{ -1 };
    for (auto i = 0; i < reindeers.size(); ++i)
    {
      Number distanceTravelled = reindeers[i].GetDistanceAt(t);
      if (distanceTravelled > maxd)
      {
        maxd = distanceTravelled;
        maxi = i;
      }
    }
    assert(maxi >= 0);
    ++points[maxi];
  }

  Number maxpoints{ -1 };
  for (auto i = 0; i < reindeers.size(); ++i)
  {
    if (points[i] > maxpoints) maxpoints = points[i];
  }
  return maxpoints;
}
