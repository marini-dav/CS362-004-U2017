#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	//Test random characters specified in testme()
    char character;
	//Make a random character based on the following switch statement, modulus by 10 because there are nine characters passed in main
	int random = rand() % 10;
	//Each case is a character from main in order, character is initialized to a random character and then we break out of the switch statement.
	switch (random) {
	case 1:
		character = '[';
		break;
	case 2:
		character = '(';
		break;
	case 3:
		character = '{';
		break;
	case 4:
		character = ' ';
		break;
	case 5:
		character = 'a';
		break;
	case 6:
		character = 'x';
		break;
	case 7:
		character = ')';
		break;
	case 8:
		character = '}';
		break;
	case 9:
		character = ']';
		break;
	}
	//Return the random character created
	return character;
}

char *inputString()
{
	int i, j;
	char reset[5] = { 'r', 'e', 's', 'e', 't' };
	
	char string[6];
	//Intialize the last character of our string as the null character
	string[6] = '\0';
	//Half of the time
	if ((rand() % 10) > 1) {
		//Put random alphanumeric and symbol characters in our string
		for (i = 0; i < 5; i++){
			string[i] = (rand() % 95) + 32;
		}
	}
	//Otherwise, only use the letters from reset
	else {
		for (i = 0; i < 5; i++) {
			string[i] = reset[i];
		}
	}
	return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
