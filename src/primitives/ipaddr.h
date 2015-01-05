#ifndef NX_IPADDR_H
#define NX_IPADDR_H

#include <stddef.h>

#define IPADDR_LEN 4

typedef struct _ipaddr_t {
	// Le type de la valeur de base est uchar (8 bits)
	// pour éviter les confusions entre les differents
	// modeles de donnees LP32, ILP32, LLP64 et LP64
	//
	// Une IP est codee sur 4 octets, donc uchar[4]
	unsigned char address[IPADDR_LEN];
} ipaddr_t;

/** ipaddr_fsstr
 *
 * From sized string to a ipaadr_t
 */
ipaddr_t ipaddr_fsstr(unsigned char* data, size_t length);

/** ipaddr_cstr
 *
 * Print a ipaadr_t like ddd.ddd.ddd.ddd
 */
const char* ipaddr_cstr(ipaddr_t ip);

/** ipaddr_coid
 *
 * Print a ipaadr_t like ddd.ddd.ddd.ddd
 * Aka ipaddr_cstr
 */
const char* ipaddr_coid(ipaddr_t ip);

#endif
