#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), 
  ava_capacity_( capacity ), internal_buffer_(),  is_closed_( false ),
  bytes_pushed_( 0 ), bytes_popped_( 0 ) {}

void Writer::push( string data )
{
  // Your code here.
  if( data.empty() || ava_capacity_ == 0 ) return ;
  if( data.size() > ava_capacity_ ) {
    internal_buffer_.push_back( data.substr(0, ava_capacity_) );
    bytes_pushed_ += ava_capacity_;
    ava_capacity_ = 0;
  } else {
    internal_buffer_.push_back( data );
    bytes_pushed_ += data.size();
    ava_capacity_ -= data.size();
  }
}

void Writer::close()
{
  // Your code here.
  is_closed_ = true;
}

bool Writer::is_closed() const
{
  return is_closed_; // Your code here.
}

uint64_t Writer::available_capacity() const
{
  return ava_capacity_; // Your code here.
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_; // Your code here.
}

string_view Reader::peek() const
{
  if ( internal_buffer_.empty() ) return {};
  return internal_buffer_.front(); // Your code here.
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  uint64_t to_popped = len;
  while ( to_popped && internal_buffer_.size() ) {
    uint64_t next_popped = internal_buffer_.front().size();
    if( to_popped >= next_popped ) {
      internal_buffer_.pop_front();
      bytes_popped_ += next_popped;
      ava_capacity_ += next_popped;
      to_popped -= next_popped;
    } else {
      auto s = internal_buffer_.front();
      internal_buffer_.pop_front();
      internal_buffer_.push_front(s.substr(to_popped));
      bytes_popped_ += to_popped;
      ava_capacity_ += to_popped;
      to_popped = 0;
    }
  }
}

bool Reader::is_finished() const
{
  return is_closed_ && internal_buffer_.size() == 0; // Your code here.
}

uint64_t Reader::bytes_buffered() const
{
  return bytes_pushed_ - bytes_popped_; // Your code here.
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_; // Your code here.
}

