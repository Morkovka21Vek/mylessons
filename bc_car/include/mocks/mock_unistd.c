ssize_t read_ExpectAndReturn(int fd, void *buf, size_t count, ssize_t returned_val)
{
  return returned_val;
}

ssize_t write_ExpectAndReturn(int fd, const void *buf, size_t count, ssize_t returned_val)
{
  return returned_val;
}
