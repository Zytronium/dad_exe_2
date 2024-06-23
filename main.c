#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int t = 1;

char *strlwr_(char *s) {
	int i;
	char *newStr = strdup(s);

	for (i = 0; newStr[i]; i++) {
		if (newStr[i] >= 'A' && newStr[i] <= 'Z')
			newStr[i] += 32;
	}
	return newStr;
}

char *strupr_(char *s) {
	int i;
	char *newStr = strdup(s);

	for (i = 0; newStr[i]; i++) {
		if (newStr[i] >= 'a' && newStr[i] <= 'z')
			newStr[i] -= 32;
	}
	return newStr;
}

void println(const char *msg, ...) {
	va_list arg;

	va_start (arg, msg);
	vfprintf (stdout, msg, arg);
	putchar('\n');
	va_end (arg);
}

int xor(int numConditions, ...) {
	va_list arg;
	int n = 0, i;

	va_start(arg, numConditions);
	for (i = 0; i < numConditions; i++) {
		if (va_arg(arg, int))
			n++;
		if (n > 1)
			break;
	}
	va_end(arg);

	return (n == 1);
}

char *timeElapsed() {
	int tm = t;
	int hrs = 0, dys = 0, wks = 0, mnths = 0, yrs = 0;
	int andPos = 0; /*0 = not used, 1 = after days, 2 = after weeks, 3 = after months, 4 = after years*/

	while (tm > 0) {
		if (tm >= 8760) {
			tm -= 8760;
			yrs++;
		} else if (tm >= 730) {
			tm -= 730;
			mnths++;
		} else if (tm >= 168) {
			tm -= 168;
			wks++;
		} else if (tm >= 24) {
			tm -= 24;
			dys++;
		} else if (tm < 24) {
			hrs = tm;
			tm = 0;
		}
	}

	if (yrs != 0 && xor(4, mnths != 0, wks != 0, dys != 0, hrs != 0)) {
		andPos = 4;
	} else if (mnths != 0 && xor(3, wks != 0, dys != 0, hrs != 0)) {
		andPos = 3;
	} else if (wks != 0 && xor(2, dys != 0, hrs != 0)) {
		andPos = 2;
	} else if (dys != 0 && hrs != 0) {
		andPos = 1;
	}

	char* result = malloc(64);
	char yearsStr[13];
	char monthsStr[12];
	char weeksStr[10];
	char daysStr[9];
	char hoursStr[9];

	if (yrs != 0) {
		sprintf(yearsStr, (yrs == 1) ? "%d year%s" : "%d years%s", yrs, (andPos == 4 || andPos == 0) ? ((hrs == 0 && dys == 0 && wks == 0 && mnths == 0) ? "" : " ") : ", ");
	} else {
		yearsStr[0] = '\0';
	}

	if (mnths != 0) {
		sprintf(monthsStr, (mnths == 1) ? "%d month%s" : "%d months%s", mnths, (andPos == 4 || andPos == 0 || (andPos == 3 && yrs == 0)) ? ((hrs == 0 && dys == 0 && wks == 0) ? "" : " ") : ", ");
	} else {
		monthsStr[0] = '\0';
	}

	if (wks != 0) {
		sprintf(weeksStr, (wks == 1) ? "%d week%s" : "%d weeks%s", wks, (andPos >= 3 || andPos == 0 || (andPos == 2 && yrs == 0 && mnths == 0)) ? ((hrs == 0 && dys == 0) ? "" : " ") : ", ");
	} else {
		weeksStr[0] = '\0';
	}

	if (dys != 0) {
		sprintf(daysStr, (dys == 1) ? "%d day%s" : "%d days%s", dys, (andPos >= 2 || andPos == 0 || (andPos == 1 && yrs == 0 && mnths == 0 && wks == 0)) ? ((hrs == 0) ? "" : " ") : ", ");
	} else {
		daysStr[0] = '\0';
	}

	if (hrs != 0) {
		sprintf(hoursStr, (hrs == 1) ? "1 hour" : "%d hours", hrs);
	} else {
		hoursStr[0] = '\0';
	}

	sprintf(result, "%s%s%s%s%s%s%s%s%s",
			yearsStr,
			(andPos == 4) ? "and " : "",
			monthsStr,
			(andPos == 3) ? "and " : "",
			weeksStr,
			(andPos == 2) ? "and " : "",
			daysStr,
			(andPos == 1) ? "and " : "",
			hoursStr
	);

	return result;
}

char *timeElapsedShort() { /* WIP. High priority */
	return "10 Years";
}

void returnWithMilk() {
	println("Dad has left the store and is returning home with the milk.");
	sleep(3);
	printf("Dad: ");
	sleep(1);
	println("\"I'm home! I finally found the milk!\"");
	sleep(1);
	printf("You: ");
	sleep(1);
	printf("\" .");
	sleep(1);
	printf(".");
	sleep(1);
	printf(".");
	sleep(2);
	printf(" What? DAD!? ");
	sleep(1);
	println("IT'S BEEN %s!\"", strupr_(timeElapsedShort()));
	sleep(3);
	println("\n T H E    E N D ");
	sleep(12);
	println("Type anything and press enter the exit program.");
	scanf("\n");
}

void dad(int c, char *storeItems[]) {
	srand(time(NULL));
	println("Dad is searching for the milk... (time elapsed: %s)", timeElapsed());
	free(timeElapsed());

	t++;
	sleep(2);

	if (strcmp((char *) strlwr_(storeItems[rand() % c]), "milk") == 0) {
		println("\nDad has found the milk.\n");
		sleep(2);
		returnWithMilk();
	} else {
		dad(c, storeItems);
	}
}

int main(int argc, char *argv[]) {
	println("Dad.Exe 2 is running.");
	sleep(2);
	if (argc == 1) {
		println("Dad: Hi bud. Do you need me to go get some milk?\n");
		println("Dad.Exe 2 has ended. To run Dad.Exe 2, Insert a list "
				"of store items, separated by spaces, encased in quotes if "
				"there is more than one word in an item. Usage: %s storeItem1 "
				"'store item 2' store_Item_3 milk 'or no milk' (etc)", argv[0]);
		return 0;
	}
	if (strcmp((char *) strlwr_(argv[1]), "milk") == 0 && argc == 2) /*TODO: detect if there are multiple parameters but they are all "milk"*/
		println("Really? The store only sells milk? Okay.\n");
	sleep(1);
	println("Dad has left to get the milk.");
	sleep(1);
	println("Dad will come back when he has found the milk.");
	sleep(2);
	/*TODO: create a new argv variable that doesn't contain argv[0], and pass it on to dad()*/
	dad(argc, argv);

	return 0;
}
