/*
 * Best is shorthand for bestoso
 *
 * This header file defines a reliable modular function
 * I was sick of the flawed % and remainder(), so, here
 * you go!
 *
 * The f(field size) must be unsigned to prevent overflow.
 * To use a negative field size, you must multiply your
 * return value by -1 :)
 *
 * If f is == 0 then the function will retuen -1 without
 * printing a waring. use this value to detect improper use
 *
 * Built by Alex Bestoso
 */

signed int bestModu(signed int n, size_t f){
	signed int ret = 0;
	if(f == 0){
		return -1;
	}
	
	if(n == 0){
	/*
	 * returning 0 because that is what the
	 * result would be!
	 */
		return 0;

	}else if(n >= 1){
	/* calculate the working % relative to
	 * positive numbers!
	 */	
		while(n >= 1){
			ret++;				/* increment ret*/
			
			if(ret >= f || ret <= -1)	/* is ret outside of the finite field? -1 is bc hackers*/
				ret = 0;		/* yes, set to 0 bc if ret >= f we land in a nonexisting "pie slice"*/
							/* no, rets value is correct */
			n--;				/* decrement the amount of steps remaining */
		}	
		return ret;				/* return result when n is a positive number */
	}else{
	/* calculate the working % relative to
         * negative numbers!
         */
		while(n <= -1){
			ret--;				/* decrement ret */
			if(ret <= -1 || ret >= f)	/* is ret negative? f is bc hackers */
				ret = f-1;		/* yes, set ret to f-1 bc to the left of 0 is f-1, not -1(positve amt of "pie slices")*/
							/* no, rets value is correct */
			n++;				/* decrement total amunt of required steps. */
		}
		return ret;
	}

	/* incase of undefined errror */
	ret = 1;
	return ret;
}

signed int bestEuclideanAlgo(signed int fieldSize, signed int number){
	signed int ret = 0, comp = 99, tmpI = 0, tmpII;
	signed int rounds = 0;
	if(number > fieldSize){
		tmpI = number;
		number = fieldSize;
		fieldSize = number;
	}
	while(comp != 0){
		if(rounds == 0){
			comp = bestModu(fieldSize, (size_t)number);
			if(comp != 0){
				ret = comp;
			}
			rounds = 1;

		}else if(rounds == 1){
			tmpI = comp;
			comp = bestModu(number, (size_t)comp);
			if(comp != 0){
				ret  = comp;
			}
			rounds = 2;		

		}else if(rounds == 2){
			tmpII = comp;
			comp = bestModu(tmpI, (size_t)comp);
			if(comp != 0){
				ret = comp;
			}
			rounds = 3;
			
		}else if(rounds == 3){
			tmpI = comp;
			comp = bestModu(tmpII, (size_t)comp);
			if(comp != 0){
				ret = comp;
			}
			rounds = 2;

		}
	}
	return ret;
}

signed int bestMultiInvers(signed int fieldSize, signed int number){
	int ret = 0, tmp=0;
	for(int i=0; i<fieldSize; i++){
		ret = i;
		tmp = bestModu(number * i, fieldSize);
		if(tmp == 1){
			return ret;
		}
	}
	ret = -1;
	return ret;
}
