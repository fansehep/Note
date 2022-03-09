#### 引言 : 在服务器编程的过程中，时间是非常重要的，无论是定时器的函数执行，回调函数的执行，各种连接的判断都需要一个准确的时间。
#### muduo 使用 TimeStamp 来处理时间的一些判断。
==一些不重要的细节在这里省略==
```c++
class Timestamp : ...{
	public:
		...
	private:
		int64_t microSecondsSinceEpoch;
};
```
- Timestamp 类只有一个成员 microSecondsSinceEpoch ,该类单位为微秒。所以我们一般使用的时候可以不用应用传递或者指针传递。
- <font color = red> 此处说明一些较为基本类型 <font color = black>
	- muduo::copyable 继承此类者 该类可拷贝
	- muduo::noncopyable 继承此类者 该类不可拷贝 
- SinceEpoch 表示距离 Linux 时间元的时间。类Unix时间以时间元为起始时间
#### 函数剖析
```c++
// 默认构造函数
    Timestamp() {}
    // 传入自时间元的微妙 ，并返回
    explicit Timestamp(int64_t MicroSecondSinceEpocharg);
    // 交换 各自时间.
    void swap(Timestamp& that);
    // 转化为字符串并且返回 该函数会调用 toFormattedString 
    std::string toString() const;
    // 转化为字符串并且返回 ， 该函数默认 为 true , 为true 则显示微妙
    std::string toFormattedString(bool showMicroSeconds = true);
    // 判断当前时间是否合理
    bool valid() const;
    // 返回自 unix 时间元的时间 微妙
    int64_t MicroSecondsSinceEPoch() const;
    // 返回秒数 
    time_t  secondsSinceEpoch() const;
    // 返回当前承载当前时间的时间戳
    static Timestamp now();
    // 返回一个不可靠的时间戳
    static Timestamp invalid();
    // 返回传入 ths 的时间戳
    static Timestamp fromUnixTime(time_t ths);
    static Timestamp fromUnixTime(time_t ths, int microSeconds);
	// kMicroSecondsPerSecond 后面取秒数有用
    static const int kMicroSecondsPerSecond = 1000 * 1000;
	// 返回两个时间戳的时间差
	inline double TimeDifference(Timestamp high, Timestamp low);
	// 给一个时间戳增加时间
	inline Timestamp addTime(Timestamp timestamp, double seconds);
```