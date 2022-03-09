- Channel 类是通道类，主要负责 套接字的 IO 事件的分发，
	- 他拥有注册回调函数的方法，具体从哪儿注册，我们后面说。
	- 他有一套函数，可以对channel 所对应的套接字的属性进行设置。
	- 我们来看看这一套接口。但是每一次的调用都会调用 update 函数
```c++
void Channel::update()
{
  addedToLoop_ = true;
  loop_->updateChannel(this);
}
```
- 会调用 private : EventLoop->updateChannel(this)
```c++

void EventLoop::updateChannel(Channel* channel)
{
  assert(channel->ownerLoop() == this);
  assertInLoopThread();
  poller_->updateChannel(channel);
}
```
- 从而调用 poller_->updateChannel 的方法
	- 这里 poller_ 是一个纯虚基类，我们这里看 pollpoller 的实现
```c++
void PollPoller::updateChannel(Channel* channel)
{
  Poller::assertInLoopThread();
  LOG_TRACE << "fd = " << channel->fd() << " events = " << channel->events();
  // 如果该 Channel 刚刚构造出来index = -1
  if (channel->index() < 0)
  {
    // a new one, add to pollfds_
    assert(channels_.find(channel->fd()) == channels_.end());
    struct pollfd pfd;
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
	  // push_back 到 poll 中的 pollfds_中去
    pollfds_.push_back(pfd);
	  // 取到对应的index下标中
    int idx = static_cast<int>(pollfds_.size())-1;
    channel->set_index(idx);
	  // 然后增加到 std::map<int, Channel*> 中去
    channels_[pfd.fd] = channel;
  }
  else
  {
    // update existing one
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] == channel);
    int idx = channel->index();
    assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
    struct pollfd& pfd = pollfds_[idx];
    assert(pfd.fd == channel->fd() || pfd.fd == -channel->fd()-1);
    pfd.fd = channel->fd();
    pfd.events = static_cast<short>(channel->events());
    pfd.revents = 0;
    //todo 将一个通道更改为不关注事件，但不从 Poller 中移除该通道 
    if (channel->isNoneEvent())
    {
      // ignore this pollfd
	   // 暂时忽略该文件描述符的事件
		//  这里之所以没有把 pfd.fd 直接设置为 -1
		//  是因为方便优化 下面的 removeChannel 
		// 负数的文件描述符不合法，可以直接不用管。
      pfd.fd = -channel->fd()-1;
    }
  }
}
```
- 好了，我们来看看 removeChannel 吧
```c++
void PollPoller::removeChannel(Channel* channel)
{
  Poller::assertInLoopThread();
  LOG_TRACE << "fd = " << channel->fd();
  assert(channels_.find(channel->fd()) != channels_.end());
  assert(channels_[channel->fd()] == channel);
  assert(channel->isNoneEvent());
  int idx = channel->index();
  assert(0 <= idx && idx < static_cast<int>(pollfds_.size()));
  const struct pollfd& pfd = pollfds_[idx]; (void)pfd;
  assert(pfd.fd == -channel->fd()-1 && pfd.events == channel->events());
  size_t n = channels_.erase(channel->fd());
  assert(n == 1); (void)n;
	// 如果在末尾，直接 pop_back 即可。
  if (implicit_cast<size_t>(idx) == pollfds_.size()-1)
  {
    pollfds_.pop_back();
  }
  else
  {
	  // 这里如果需要删除的是在vector中间的某一个元素
	  // 我们需要用它与尾部元素交换，然后 pop 尾部元素即可。
    int channelAtEnd = pollfds_.back().fd;
    iter_swap(pollfds_.begin()+idx, pollfds_.end()-1);
	  // 复原 为 负数 的套接字
    if (channelAtEnd < 0)
    {
      channelAtEnd = -channelAtEnd-1;
    }
	  // 并且重新更新对应的map套接字下标。
    channels_[channelAtEnd]->set_index(idx);
    pollfds_.pop_back();
  }
}
```