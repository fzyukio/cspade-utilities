#ifndef UTILS_H
#define UTILS_H

#ifndef bzero
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)
#endif

#endif