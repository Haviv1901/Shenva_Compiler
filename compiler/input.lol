def printString(pChar a)
{
	int i = 0
	while (a[i] != 0)
	{
		printChar(a[i])
		i += 1
	}
}

pChar str = [13]

str[0] = 'h'
str[1] = 'e'
str[2] = 'l'
str[3] = 'l'
str[4] = 'o'
str[5] = ' '
str[6] = 'w'
str[7] = 'o'
str[8] = 'r'
str[9] = 'l'
str[10] = 'd'
str[11] = '!'
printString(str)
