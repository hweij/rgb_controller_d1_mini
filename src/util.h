#ifndef UTIL_H
#define UTIL_H
inline bool startsWith(const char *s, const char *pattern) {
  int index = 0;
  while (pattern[index] != 0) {
    if (s[index] != pattern[index])
      break;
    index++;
  }
  return (pattern[index] == 0);
}
#endif  /* UTIL_H */
