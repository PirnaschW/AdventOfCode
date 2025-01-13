//template<> auto InputData<2023, 24, A>() { return
//"19, 13, 30 @ -2,  1, -2\n"
//"18, 19, 22 @ -1, -1, -2\n"
//"20, 25, 34 @ -2, -2, -4\n"
//"12, 31, 28 @ -1, -2, -1\n"
//"20, 19, 15 @  1, -5, -3\n"
//"Area: 7, 27";}; // Result: 2
template<> Number AoC<2023, 24, A>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Real = long double;

  Number areaMin{200'000'000'000'000};
  Number areaMax{400'000'000'000'000};

  if (v[std::ssize(v) - 1][0] == 'A')  // test data?
  {
    int z = sscanf_s(v[std::ssize(v) - 1].c_str(), "Area:%lld,%lld", &areaMin, &areaMax);
    assert(z == 2);
    v.pop_back();
  }

  class Hail
  {
  public:
    Number x;
    Number y;
    Number z;
    Number vx;
    Number vy;
    Number vz;
    Real m;
    Real b;
    bool hits;
    bool hitsInFuture;
  };
  std::vector<Hail> hail{};

  for (const auto& line : v)
  {
    Hail h;
    int z = sscanf_s(line.c_str(), "%lld,%lld,%lld @ %lld,%lld,%lld", &h.x, &h.y, &h.z, &h.vx, &h.vy, &h.vz);
    assert(z == 6);
    h.hits = true;

    // create mx+b form; m = vy/vx, b = y - x*vy/vx
    if (h.vx == 0)  // vertical 
    {
      if (h.x < areaMin || h.x > areaMax) h.hits = false;
      if (h.vy == 0)
      {
        if (h.y < areaMin || h.y > areaMax) h.hits = false;
      }
      else
      {
        Real tt = static_cast<Real>(areaMin - h.y) / h.vy;
        Real tb = static_cast<Real>(areaMax - h.y) / h.vy;
        if (tt < 0 && tb < 0) h.hits = false;
      }
    }
    else
    {
      h.m = static_cast<Real>(h.vy) / h.vx;
      h.b = static_cast<Real>(h.y) - static_cast<Real>(h.x * h.vy) / h.vx;

      // x = left (7): => tl = time when hitting left side
      // x = right (27): => tr = time when hitting left side
      Real tl = static_cast<Real>(areaMin - h.x) / h.vx;
      Real tr = static_cast<Real>(areaMax - h.x) / h.vx;
      if (tl < 0 && tr < 0) h.hits = false;

      // x = left (7): => yl = m*7+b
      // x = right (27): => yr = m*27+b
      Real yl = h.m * areaMin + h.b;
      Real yr = h.m * areaMax + h.b;
      // yl > top && yr > top -> out
      // yl < bottom && yr < bottom -> out
      // otherwise in
      if (yl > areaMax && yr > areaMax) h.hits = false;
      if (yl < areaMin && yr < areaMin) h.hits = false;
    }
    hail.push_back(h);
  }


  Number count{ 0 };
  for (int i = 0; i < std::ssize(hail); ++i)
  {
    if (!hail[i].hits) continue;
    for (int j = i + 1; j < std::ssize(hail); ++j)
    {
      if (!hail[j].hits) continue;

      // intersection at:
      // m1 == m2 => out
      if (hail[i].m == hail[j].m)
      {
        if (hail[i].b != hail[j].b) continue;
      }
      else
      {
        // ix = -(b2-b1)/(m2-m1)
        // iy = (b1m2-m1b2)/(m2-m1)
        Real ix = -(hail[j].b - hail[i].b) / (hail[j].m - hail[i].m);
        if (ix < areaMin || ix > areaMax) continue;
        Real iy = (hail[i].b * hail[j].m - hail[i].m * hail[j].b) / (hail[j].m - hail[i].m);
        if (iy < areaMin || iy > areaMax) continue;

        // time conditions:
        // intersect times:
        // t1 = ( -(b2-b1)/(m2-m1)-x1 ) / vx1
        // t2 = ( -(b2-b1)/(m2-m1)-x2 ) / vx2
        Real t1 = (ix - hail[i].x) / hail[i].vx;
        if (t1 < 0) continue;
        Real t2 = (ix - hail[j].x) / hail[j].vx;
        if (t2 < 0) continue;
        ++count;
      }
    }
  }
  return count;
}

//template<> auto InputData<2023, 24, B>() { return
//"19, 13, 30 @ -2,  1, -2\n"
//"18, 19, 22 @ -1, -1, -2\n"
//"20, 25, 34 @ -2, -2, -4\n"
//"12, 31, 28 @ -1, -2, -1\n"
//"20, 19, 15 @  1, -5, -3\n"
//"Area: 7, 27";}; // Result: 2
template <typename T>
class Vector3D
{
public:
  T x;
  T y;
  T z;
public:
  Vector3D operator - (const Vector3D& v) const noexcept { return { x - v.x, y - v.y, z - v.z }; }
  Vector3D operator + (const Vector3D& v) const noexcept { return { x + v.x, y + v.y, z + v.z }; }
  Vector3D operator / (const T& s) const noexcept { return { x / s, y / s, z / s }; }
  Vector3D operator * (const T& s) const noexcept { return { x * s, y * s, z * s }; }
  Vector3D CrossProduct(const Vector3D& v) const noexcept { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }
  T DotProduct(const Vector3D& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
};
template<> Number AoC<2023, 24, B>(std::istream& input)
{
  using Input = std::vector<std::string>;
  Input v = ReadLines(input);  // read all lines into vector

  using Real = long double;


  Number areaMin{200'000'000'000'000};
  Number areaMax{400'000'000'000'000};

  if (v[std::ssize(v) - 1][0] == 'A')  // test data?
  {
    int z = sscanf_s(v[std::ssize(v) - 1].c_str(), "Area:%lld,%lld", &areaMin, &areaMax);
    assert(z == 2);
    v.pop_back();
  }

  class Hail
  {
  public:
    Vector3D<Real> p;
    Vector3D<Real> v;
    Real m;
    Real b;
    bool hits;
  };
  std::vector<Hail> hail{};

  for (const auto& line : v)
  {
    Vector3D<Number> p;
    Vector3D<Number> v;
    int z = sscanf_s(line.c_str(), "%lld,%lld,%lld @ %lld,%lld,%lld", &p.x, &p.y, &p.z, &v.x, &v.y, &v.z);
    assert(z == 6);
    Hail h;
    h.p.x = static_cast<Real>(p.x);
    h.p.y = static_cast<Real>(p.y);
    h.p.z = static_cast<Real>(p.z);
    h.v.x = static_cast<Real>(v.x);
    h.v.y = static_cast<Real>(v.y);
    h.v.z = static_cast<Real>(v.z);
    hail.push_back(h);
  }

  auto CalculateRock = [](const Vector3D<Real>& p1o, const Vector3D<Real>& p2o, const Vector3D<Real>& p3o, const Vector3D<Real>& v1o, const Vector3D<Real>& v2o, const Vector3D<Real>& v3o) -> Vector3D<Real>
    {
      // express hail 2 and 3 in coordinates of hail 1 (so hail 1 will be 0,0 all the time)
      // p2' = p2 - p1
      // v2' = v2 - v1
      // p3' = p3 - p1
      // v3' = v3 - v1
      Vector3D<Real> p2 = p2o - p1o;
      Vector3D<Real> v2 = v2o - v1o;
      Vector3D<Real> p3 = p3o - p1o;
      Vector3D<Real> v3 = v3o - v1o;

      //
      // p2, p3 collisions with rock are at:
      // p2' + t2 * v2'
      // p3' + t3 * v3'
      //
      // p1 hits the rock at 0,0 = origin and it must be in one line with the other two - the rock doesn't change direction!
      // so:
      // (p2' + t2 * v2') x (p3' + t3 * v3') = 0 (cross product of collinear vectors is 0)
      // ==>
      // (p2' x p3') + t2 * (v2' * p3') + t3 * (p2' x v3') + t2 * t3 * (v2' x v3') = 0
      // 
      // for any two vectors a and b, cross product then dot product give 0:
      // (a x b) . a = (a x b) . b = 0
      //
      // we dot-multiply with v3':
      // ((p2' x p3') + t2 * (v2' * p3') + t3 * (p2' x v3') + t2 * t3 * (v2' x v3'))   . v3' = 0
      // (p2' x p3') . v3' + t2 * (v2' * p3') . v3' + t3 * 0 + t2 * t3 * 0 = 0
      // (p2' x p3') . v3' + t2 * (v2' * p3') . v3' = 0
      // solve for t2:
      // t2 = -((p2' x p3') . v3') / ((v2' * p3') . v3')
      //
      // same dot product instead of v3' with v2':
      // (p2' x p3') . v2' + t3 * (p2' x v3') . v2' = 0
      // t3 = -((p2' x p3') . v2') / ((p2' * v3') . v2')
      //

      // t2 = -((p2' x p3') . v3') / ((v2' * p3') . v3')
      Real t2 = -p2.CrossProduct(p3).DotProduct(v3) / v2.CrossProduct(p3).DotProduct(v3);
      // t3 = -((p2' x p3') . v2') / ((p2' * v3') . v2')
      Real t3 = -p2.CrossProduct(p3).DotProduct(v2) / p2.CrossProduct(v3).DotProduct(v2);
      if (t3 == t2) return { 0, 0, 0 }; // collinear input, doesn't work

      // with t2 and t3, we can find the collision points c2 and c3
      Vector3D<Real> c2 = p2o + v2o * t2;
      Vector3D<Real> c3 = p3o + v3o * t3;

      // finally, the rock's data:
      Vector3D<Real> rv{ (c3 - c2) / (t3 - t2) };
      Vector3D<Real> r{ c2 - rv * t2 };
      return r;
    };
  
  int s = static_cast<int>(std::ssize(hail));
  Vector3D<Real> rock{};
  for (int i = 0; i < s; i++)
  {
    rock = CalculateRock(hail[i%s].p, hail[(i + 1)%s].p, hail[(i + 2)%s].p, hail[i%s].v, hail[(i + 1)%s].v, hail[(i + 2)%s].v);
//    std::cout << "Rock: " << rock.x << ", " << rock.y << ", " << rock.z << "; Sum= " << rock.x + rock.y + rock.z << std::endl;
    if (rock.x > 0) break;
  }

  Vector3D<Number> rockNumber{};
  rockNumber.x = static_cast<Number>(rock.x + 0.4); // to correct for potential rounding errors (there were none, though!)
  rockNumber.y = static_cast<Number>(rock.y + 0.4); 
  rockNumber.z = static_cast<Number>(rock.z + 0.4); 
  return rockNumber.x + rockNumber.y + rockNumber.z;
}
