#ifndef RTIMER_ARCH_H_
#define RTIMER_ARCH_H_
#ifdef __cplusplus
extern "C" {
#endif

#define RTIMER_ARCH_SECOND CLOCK_CONF_SECOND

#define rtimer_arch_now() clock_time()

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif /* RTIMER_ARCH_H_ */