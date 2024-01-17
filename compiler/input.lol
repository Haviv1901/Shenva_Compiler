int a = intInput(), b = 1, c = 1
bool is_boom = false

for (b <= a, b += 1)
{
	if (b % 7 == 0)
	{
		is_boom = true
	}
	
	
	if (is_boom)
	{
		printInt(-1)
		is_boom = false
	}
	else
	{
		printInt(b)
	}
	printChar('\n')
}






