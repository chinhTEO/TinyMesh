#include <signal.h>
#ifndef _WIN32
#include <sys/time.h>
#endif /* !_WIN32 */
#include <stddef.h>

#include "rtimer.h"
#include "clock.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*---------------------------------------------------------------------------*/
static void
interrupt(int sig)
{
  signal(sig, interrupt);
  rtimer_run_next();
}
/*---------------------------------------------------------------------------*/
void
rtimer_arch_init(void)
{
#ifndef _WIN32
  signal(SIGALRM, interrupt);
#endif /* !_WIN32 */
}
/*---------------------------------------------------------------------------*/
void
rtimer_arch_schedule(rtimer_clock_t t)
{
#ifndef _WIN32
  struct itimerval val;
  rtimer_clock_t c;

  c = t - clock_time();
  
  val.it_value.tv_sec = c / CLOCK_SECOND;
  val.it_value.tv_usec = (c % CLOCK_SECOND) * CLOCK_SECOND;

  PRINTF("rtimer_arch_schedule time %"PRIu32 " %"PRIu32 " in %ld.%ld seconds\n",
         t, c, (long)val.it_value.tv_sec, (long)val.it_value.tv_usec);

  val.it_interval.tv_sec = val.it_interval.tv_usec = 0;
  setitimer(ITIMER_REAL, &val, NULL);
#endif /* !_WIN32 */
}
/*---------------------------------------------------------------------------*/