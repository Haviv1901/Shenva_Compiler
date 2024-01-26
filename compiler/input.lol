int b = 3

def printCharFor(int numberOfTimesToPrintChar, char charToPrint)
{
	for (numberOfTimesToPrintChar > 0, numberOfTimesToPrintChar -= 1)
	{
		printChar(charToPrint)
	}
}


printCharFor(10, 'a')
printCharFor(10, 'b')


