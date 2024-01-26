def isNumContainsSeven(int num)
{
	while(num > 0)
	{
		if (num % 10 == 7)
		{
			return true
		}
		num /= 10
	}
	return false
}



def sevenBoom(int num)
{
	int i = 1
	for (i <= num, i+= 1)
	{
		if (i % 7 == 0 or isNumContainsSeven(i) == 1)
		{
			printChar('B', 'O', 'O', 'M')
		}
		else
		{
			printInt(i)
		}
		printChar('\n')
	}
}



sevenBoom(intInput())




