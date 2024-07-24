#include "common.h"

bool cmp_sub(std::string ab, std::string c, const size_t ab_len, size_t c_pos)
{
	for (int i = 0; i < ab_len; i++, c_pos++) {
		if (ab.at(i) != c.at(c_pos)) {
			return false;
		}
	}

	return true;
}

// the contatenation is the property tha defines interleaved
bool is_interleaved(std::string& A, std::string& B, std::string& C)
{
	auto a_len = A.length();
	auto b_len = B.length();
	auto c_len = C.length();

	if((a_len + b_len) != c_len)
		return false;

	if (A.at(0) != C.at(0) && B.at(0) != C.at(0))
		return false;

	if(A.at(A.length() -1 ) != C.at(c_len -1) && B.at(b_len - 1) != C.at(c_len - 1))
		return false;

	if (a_len < b_len) {
		// do a first
		auto ret = cmp_sub(A, C, a_len, 0);
		if (!ret) {
			return false;
		}
		else {
			ret = cmp_sub(B, C, b_len, a_len);
			if (!ret) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		// do b first
		auto ret = cmp_sub(B, C, b_len, 0);
		if (!ret) {
			return false;
		}
		else {
			ret = cmp_sub(A, C, a_len, b_len);
			if (!ret) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

int main()
{
	{
		std::string a = "YX";
		std::string b = "X";
		std::string c = "XXY";
		auto ret = is_interleaved(a, b, c);
		ASSERT_EQ(ret, false);
		
	}
	{
		std::string a = "XY"; // only difference from above is order of XY
		std::string b = "X";
		std::string c = "XXY";
		auto ret = is_interleaved(a, b, c);
		ASSERT_EQ(ret, true);
	}
}