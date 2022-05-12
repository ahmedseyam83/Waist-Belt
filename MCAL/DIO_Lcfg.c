
#include "DIO_Interface.h"


	
extern const DIO_PinStatus_type PinsStatusArray[TOTAL_PINS]={
	
	INFREE,      /* Port A Pin 0 ADC 0*/ 
	INFREE,      /* Port A Pin 1 */
	INFREE,      /* Port A Pin 2 */
	INFREE,      /* Port A Pin 3 */
	INFREE,      /* Port A Pin 4 */
	INFREE,      /* Port A Pin 5 */
	INFREE,      /* Port A Pin 6 */
	INFREE,      /* Port A Pin 7 */
	OUTPUT,      /* Port B Pin 0   / */
	OUTPUT,      /* Port B Pin 1   /*/
	OUTPUT,		 /* Port B Pin 2 / INT2*/
	OUTPUT,		 /* Port B Pin 3   /OC0*/
	INFREE,		 /* Port B Pin 4 */
	INFREE,		 /* Port B Pin 5 */
	INFREE,		 /* Port B Pin 6 */
	INFREE,		 /* Port B Pin 7 */
	OUTPUT,		 /* Port C Pin 0 */
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT,		 /* Port C Pin 3 */
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */
	INFREE,		 /* Port C Pin 6 */
	INFREE,		 /* Port C Pin 7 */
	INFREE,		 /* Port D Pin 0 */
	INFREE,		 /* Port D Pin 1 */
    INLLUP,      /* Port D Pin 2 */ /*INT0 */
	INFREE,      /* Port D Pin 3 / INT1 */
	INFREE,		 /* Port D Pin 4 */
	OUTPUT,		 /* Port D Pin 5 */
	INFREE,		 /* Port D Pin 6 /   ICP*/
	INFREE		 /* Port D Pin 7 */
};	