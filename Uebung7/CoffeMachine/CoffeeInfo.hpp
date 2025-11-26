#ifndef COFFEE_INFO_HPP
#define	COFFEE_INFO_HPP

#include <string>

class CoffeeInfo {
public:

	inline static const double mEspressoPrice = 3;
	inline static const std::string mEspressoInfo = "Espresso";

	inline static const double mDecaffPrice = 2.8;
	inline static const std::string mDecaffInfo = "Decaff";

	inline static const double mMochaPrice = 2.7;
	inline static const std::string mMochaInfo = "Mocha";

	inline static const double mExtendedPrice = 5;
	inline static const std::string mExtendedInfo = "Extended One";

	inline static const double mMilkPrice = 2.5;
	inline static const std::string mMilkInfo = "Milk";

	inline static const double mSojaMilkPrice = 15;
	inline static const std::string mSojaMilkInfo = "SojaMilk";

	inline static const double mSugarPrice = 1.5;
	inline static const std::string mSugarInfo = "Sugar";

	inline static const double mCreamPrice = 2;
	inline static const std::string mCreamInfo = "Cream";

private:
};


#endif // !COFFEE_INFO_HPP
