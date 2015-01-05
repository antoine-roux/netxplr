#ifndef NX_MACADDR_H
#define NX_MACADDR_H

#include <stddef.h>

#define MACADDR_LEN 6

typedef struct _macaddr_t {
	// Le type de la valeur de base est uchar (8 bits)
	// pour éviter les confusions entre les differents
	// modeles de donnees LP32, ILP32, LLP64 et LP64
	//
	// Une MAC est codee sur 6 octets, donc uchar[6]
	unsigned char address[MACADDR_LEN];
} macaddr_t;

/** macaddr_fsstr
 *
 * From sized string to a macaadr_t
 */
macaddr_t macaddr_fsstr(unsigned char* data, size_t length);

/** macaddr_cstr
 *
 * Print a macaadr_t like xx:xx:xx:xx:xx
 */
const char* macaddr_cstr(macaddr_t mac);

/** macaddr_coid
 *
 * Print a macaadr_t like ddd.ddd.ddd.ddd.ddd.ddd
 */
const char* macaddr_coid(macaddr_t mac);

#endif
