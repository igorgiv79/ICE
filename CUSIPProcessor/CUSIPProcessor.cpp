
// Copyright © 2019 Igor Gomon

#include <iostream>
#include <fstream>
#include <iomanip>

#include <boost/lexical_cast.hpp>

using namespace boost;

struct PriceFormat {
	float price;

	PriceFormat (float f) : price (f) {}

	friend std::ostream & operator << (std::ostream &os, PriceFormat const &pp) {
		if (pp.price == -1) {
			os << "N/A";
		}
		else {
			os << pp.price;
		}

		return os;
	}
};

int main (int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "Usage: CUSIPProcessor.exe <input file name>" << std::endl;
		return -1;
	}
	
	try {
		// use the 10KB buffer to minimize disk I/O, system calls overhead etc.
		char buf[10240];
		std::ifstream ifs;
		ifs.rdbuf ()->pubsetbuf (buf, sizeof (buf));

		ifs.open (argv[1], std::ios::in);
		if (ifs.good()) {

			// read the first CUSIP;
			std::string cusip;
			std::getline (ifs, cusip);
			if (cusip.empty()) {
				std::cerr << "ERROR: Input is empty" << std::endl;
				return -2;
			}
				
			// print CUSIP;
			std::cout << cusip << ": ";

			// set the output display for the price;
			std::cout << std::fixed << std::setprecision (3);

			// go through the prices until we get to the latest one;
			float latest = -1;
			while (true) {

				// read the price;
				std::string price;
				std::getline (ifs, price);
				if (ifs.eof ())
					break;

				try {
					// does it look like a price?
					latest = boost::lexical_cast<float>(price);
				}
				catch (boost::bad_lexical_cast &) {
					// no, it is not convertible to float so it must be a CUSIP;
					std::cout << PriceFormat (latest) << "\n";
					latest = -1;
					if (!ifs.eof ()) {
						// print the next CUSIP;
						std::cout << price << ": ";
					}
				}
			}

			std::cout << PriceFormat (latest) << "\n";
		}
		else {
			std::cerr << "ERROR: Bad input" << std::endl;
			return -3;
		}
	}
	catch (std::exception const &e) {
		std::cerr << "ERROR: " << e.what () << std::endl;
		return -4;
	}
	catch (...) {
		std::cerr << "UNEXPECTED ERROR" << std::endl;
		return -4;
	}
	
	return 0;
}
