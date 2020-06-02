/* The following is a list of functions, that are useful
 * in bare-metal programming, without the use of stdlib
 * functions */

#include "../inc/libembedded.h"

char out_bytes[11]; /* used to store the output of ftoa */

/* convert a float into an ascii char array */
int ftoa(float value, int accuracy) {
        int lnum, digit, pos;
	float rnum;
        char cdigit;
	
	for(int i = 0; i < 10; i++) /* initialise out_bytes */
	        out_bytes[i] = 0x00;
	out_bytes[10] = 0x00;
		
       
	/* check that input value is within float range */
        if((value > 2147483647) || (value < -2147483647))
                return 1;
        
	lnum = (int) value; /* left side of decimal */
	rnum = value - lnum; /* right side of decimal */
	/* make rnum positive for convenience later */
	if(rnum < 0)
	        rnum -= (rnum * 2);
	
	pos = 0; /* digit position with array */
	
	/* if lhs is zero put zero before decimal
	 * otherwise, get the actual digits */
	if(!lnum) {
		out_bytes[pos] = '0';
		pos++;
	} else {
       		/* find number of digits on lhs */
		int ldigit_count, tmp;
		ldigit_count = 0;
		tmp = lnum;
		while(tmp) {
			tmp /= 10;
			ldigit_count++;	      
		}
	
		/* add numbers on lhs to out_bytes char array */
        	while(lnum && pos < 10) {
                	digit = lnum % 10;
			/* handle positive and negative ints */
			if(digit < 0) { 
				if(pos == 0) {
					out_bytes[pos] = '-';
					pos++;
					/* ldigit_count is incremented in order to 
					   progress out_bytes one step below */
					ldigit_count++;
				}
				cdigit = '0' - digit; /* dig char, case: negative */
			} else {
			        cdigit = '0' + digit; /* dig char, case: positive */
			}
			/* add lhs digits in reverse order */
               		out_bytes[--ldigit_count] = cdigit;
                	pos++;
                	lnum /= 10; /* remove another digit */
       		}
	}
	
	/* insert decimal point, only if numbers will
	 * follow decimal */
	if(accuracy && rnum > 0 && pos < 9) {
		out_bytes[pos] = '.';
		pos++;
	} else {
		return 0;
	}
	
	/* get numbers after decimal point */
	while(accuracy && rnum && pos < 10) {
		rnum *= 10;
		digit = (int) rnum;
		cdigit = '0' + digit;
		out_bytes[pos] = cdigit;
		rnum -= digit;
		pos++;
		accuracy--;
	}
	return 0;
}	
