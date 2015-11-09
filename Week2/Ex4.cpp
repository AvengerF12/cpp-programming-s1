#include <iostream>

using namespace std;

int main4()
{
	cout << "5 kg potatoes at 5p/kg" << endl \
		<< "5 m2 carpet at £5 / m2" << endl \
		<< "5 tins catfood at 5p per tin" << endl \
		<< "5 cats at £5 each" << endl \
		<< "5 bananas at 5p each" << endl;
	
	float potato = 0.05, carpet = 5.0, catfood = 0.05, cat = 5.0, banana = 0.05;

	cout << "Total cost is: " << 5 * potato + 5 * carpet + catfood * 5 + cat * 5 + banana * 5 << endl;

	return 0;
}