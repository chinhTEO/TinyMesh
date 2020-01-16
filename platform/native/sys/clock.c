#include "clock.h"
#include "platform_def.h"
#include <time.h>
#include <sys/time.h>

/*---------------------------------------------------------------------------*/
typedef struct clock_timespec_s {
  time_t  tv_sec;
  long  tv_nsec;
} clock_timespec_t;
/*---------------------------------------------------------------------------*/
static void
get_time(clock_timespec_t *spec)
{
#if defined(__linux__) || (defined(__MACH__) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200)
  struct timespec ts;

  clock_gettime(CLOCK_MONOTONIC, &ts);

  spec->tv_sec = ts.tv_sec;
  spec->tv_nsec = ts.tv_nsec;
#else
  struct timeval tv;

  gettimeofday(&tv, NULL);

  spec->tv_sec = tv.tv_sec;
  spec->tv_nsec = tv.tv_usec * 1000;
#endif
}
/*---------------------------------------------------------------------------*/
clock_time_t
clock_time(void)
{
  clock_timespec_t ts;

  get_time(&ts);

  return ts.tv_sec * CLOCK_SECOND + ts.tv_nsec / (1000000000 / CLOCK_SECOND);
}
/*---------------------------------------------------------------------------*/
unsigned long
clock_seconds(void)
{
  clock_timespec_t ts;

  get_time(&ts);

  return ts.tv_sec;
}
/*---------------------------------------------------------------------------*/
void
clock_delay(unsigned int d)
{
  /* Does not do anything. */
}
/*---------------------------------------------------------------------------*/
void
clock_init(void)
{
  /* Provide this function, required by main() */
  return;
}
/*---------------------------------------------------------------------------*/