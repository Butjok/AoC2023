#include "Day.hpp"

int main(int argc, const char* argv[]) {

	assert(argc >= 2);
	int day = std::stoi(argv[1]);

	std::cout << "Day " << day << "\n";
	std::cout << "---\n";

	switch (day) {
	case 1: Run<1>();
		break;
	case 2: Run<2>();
		break;
	case 3: Run<3>();
		break;
	case 4: Run<4>();
		break;
	case 5: Run<5>();
		break;
	case 6: Run<6>();
		break;
	case 7: Run<7>();
		break;
	case 8: Run<8>();
		break;
	case 9: Run<9>();
		break;
	case 10: Run<10>();
		break;
	case 11: Run<11>();
		break;
	case 12: Run<12>();
		break;
	case 13: Run<13>();
		break;
	case 14: Run<14>();
		break;
	case 15: Run<15>();
		break;
	case 16: Run<16>();
		break;
	case 17: Run<17>();
		break;
	case 18: Run<18>();
		break;
	case 19: Run<19>();
		break;
	case 20: Run<20>();
		break;
	case 21: Run<21>();
		break;
	case 22: Run<22>();
		break;
	case 23: Run<23>();
		break;
	case 24: Run<24>();
		break;
	case 25: Run<25>();
		break;
	default: std::cerr << "Invalid day number " << day << ".\n";
		break;
	}

	return 0;
}
