
namespace Coord2D
{
  using Coord = signed short;
  class Direction
  {
  public:
    constexpr Direction(Coord dx_, Coord dy_) noexcept : dx{ dx_ }, dy{ dy_ } {}
    constexpr bool operator ==(const Direction& d) const noexcept { return dx == d.dx && dy == d.dy; }
    constexpr Direction operator *(int factor) const noexcept { return Direction{ static_cast<Coord>(dx * factor), static_cast<Coord>(dy * factor) }; }
    constexpr Direction TurnRight() const noexcept { return Direction{ static_cast<Coord>(-dy), dx }; }
    constexpr Direction TurnLeft() const noexcept { return Direction{ dy, static_cast<Coord>(-dx) }; }
  public:
    Coord dx;
    Coord dy;
  };

  class Point
  {
  public:
    constexpr Point(Coord x_, Coord y_) noexcept : x{ x_ }, y{ y_ } {}
    constexpr bool operator ==(const Point& p) const noexcept { return x == p.x && y == p.y; }
    constexpr Point operator +(const Direction& d) const noexcept { return { static_cast<Coord>(x + d.dx), static_cast<Coord>(y + d.dy) }; }
    constexpr Point& operator +=(const Direction& d) noexcept { x += d.dx; y += d.dy; return *this; };
  public:
    Coord x;
    Coord y;
  };

  const Direction GoNull{ 0,  0 };
  const Direction GoLeft{ -1,  0 };
  const Direction GoRight{ +1,  0 };
  const Direction GoUp{ 0, -1 };
  const Direction GoDown{ 0, +1 };
  const Direction GoDownRight{ +1, +1 };
  const Direction GoDownLeft{ -1, +1 };
  const Direction GoUpRight{ +1, -1 };
  const Direction GoUpLeft{ -1, -1 };

  class V2D
  {
  public:
    V2D() = delete;
    V2D(const Input& v) noexcept : v_{ v }, sizeX_{ static_cast<Coord>(v[0].size()) }, sizeY_{ static_cast<Coord>(v.size()) } {};
    char GetChar(const Point& p) const noexcept { return v_[p.y][p.x]; }
    bool IsValid(const Point& p) const noexcept
    {
      if (p.x < 0 || p.x >= sizeX_) return false;
      if (p.y < 0 || p.y >= sizeY_) return false;
      return true;
    }
    Coord SizeX() const noexcept { return sizeX_; }
    Coord SizeY() const noexcept { return sizeY_; }

    const Input& v_;
    const Coord sizeX_;
    const Coord sizeY_;
  };
}
