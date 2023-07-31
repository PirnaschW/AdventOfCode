template<> Number AoC<2019, 8, A>(std::istream& input)
{
  constexpr Number imageWidth = 25;
  constexpr Number imageHeight = 6;
  constexpr Number imageSize = imageWidth * imageHeight;

  std::string line{};
  getline(input, line);

  assert(line.size() / imageSize * imageSize == line.size());  // must be an integer multiple of layer size

  struct Layer {
    std::array<Number,10> counts{};
  };

  std::vector<Layer> layers{};

  Number min0n = std::numeric_limits<Number>::max();
  Number min0i = -1;

  for (int i = 0; i < line.size() / imageSize; ++i)
  {
    Layer l{};

    for (int z = 0; z < imageSize; z++)
    {
      ++l.counts[line[i * imageSize + z] - '0'];
    }

    layers.push_back(l);

    if (l.counts[0] < min0n)
    {
      min0n = l.counts[0];
      min0i = i;
    }
  }

  return layers[min0i].counts[1] * layers[min0i].counts[2];
}

template<> Number AoC<2019, 8, B>(std::istream& input)
{
  constexpr size_t imageWidth = 25;
  constexpr size_t imageHeight = 6;
  constexpr size_t imageSize = imageWidth * imageHeight;

  std::string line{};
  getline(input, line);

  assert(line.size() / imageSize * imageSize == line.size());  // must be an integer multiple of layer size

  class Layer {
  public:
    Layer(std::string_view s) : s_(s) { SetCounts(); }
    const std::array<Number, 10>& GetCounts() const { return counts_; }
    const char& operator [](size_t i) const { return s_[i]; }

  private:
    void SetCounts() { for (int z = 0; z < imageSize; z++) ++counts_[s_[z] - '0']; }

  private:
    std::array<Number, 10> counts_{};
    const std::string_view s_;
  };

  std::vector<Layer> layers{};

  Number min0n = std::numeric_limits<Number>::max();
  Number min0i = -1;
  
  for (int i = 0; i < line.size() / imageSize; ++i)
  {
    Layer l(std::string_view(line.c_str() + i * imageSize, imageSize));
    layers.push_back(l);

    if (l.GetCounts()[0] < min0n)
    {
      min0n = l.GetCounts()[0];
      min0i = i;
    }
  }

  auto GetPixel = [&layers](auto &self, size_t i, size_t depth) -> char
  {
    const auto& c = layers[depth][i];
    return c == '2' ? self(self, i, depth + 1) : c;
  };

  std::array<char, imageSize> image{};
  for (int i = 0; i < imageSize; ++i)
  {
    image[i] = GetPixel(GetPixel, i, 0L);
  }

  std::string result{};
  result += '\n';
  for (int y = 0; y < imageHeight; ++y)
  {
    for (int x = 0; x < imageWidth; ++x)
    {
      result += (image[y * imageWidth + x] == '0' ? ' ' : '#');
    }
    result += '\n';
  }
  throw result;
}
