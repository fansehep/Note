#### 引言 : 由于每个地区的所使用的时间不一样，并不是所有的区域都以 UTC 时间为准。所以 muduo 引入了 TimeZone 来标记时间。
```c++
class TimeZone : public mini_muduo::copyable
{
  public:
    explicit TimeZone(const char* zonefile);
    TimeZone(int eastofUTC, const char* tzname);
    TimeZone() = default;


    bool valid() const
    {
      return static_cast<bool>(data_);
    }

    struct tm toLocalTime(time_t secondsSinceEpoch) const;
    time_t fromLocalTime(const struct tm&) const;

    static struct tm toUTCtime(time_t secondsSinceEpoch, bool yday = false);

    static time_t fromUTCtime(const struct tm&);

    static time_t fromUTCtime(int year, int month, int day,
                              int hour, int minute, int seconds);

  struct Data;

  private:
  		//
    std::shared_ptr<Data> data_;
};
```