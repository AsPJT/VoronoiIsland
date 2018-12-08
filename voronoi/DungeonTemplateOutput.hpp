#pragma once
#include <iostream>

namespace dtl {

	//�o��
	template<typename STL_>
	constexpr void outputBool(const STL_& vec_, const char* const true_str_, const char* const false_str_) {
		for (const auto& i : vec_) {
			for (const auto& j : i) {
				if (j) std::cout << true_str_;
				else std::cout << false_str_;
			}
			std::cout << std::endl;
		}
	}

	template<typename STL_>
	constexpr void outputBoolBitSet(const STL_& vec_, const char* const true_str_, const char* const false_str_) {
		for (const auto& i : vec_) {
			for (std::size_t j = 0; j < i.size(); ++j) {
				if (i[j]) std::cout << true_str_;
				else std::cout << false_str_;
			}
			std::cout << std::endl;
		}
	}

	template<typename STL_>
	constexpr void output(const STL_& vec_, const char* const str_) {
		for (const auto& i : vec_) {
			for (const auto& j : i)
				std::cout << j << str_;
			std::cout << std::endl;
		}
	}

	template<typename STL_, typename Int_>
	constexpr void noiseBool(STL_& vec_, const double rbool_, const Int_ true_tile_ = 1, const Int_ false_tile_ = 0) {
		for (auto&& i : vec_)
			for (auto&& j : i) {
				if (!rnd.randBool(rbool_)) continue;
				if (j) j = false_tile_;
				else j = true_tile_;
			}
	}

	//�m�C�Y�𔭐�������
	template<typename STL_>
	constexpr void noiseShoreBool(STL_& vec_, const double rbool_) {
		for (std::size_t i{ 1 }; i < vec_.size(); ++i)
			for (std::size_t j{ 1 }; j < vec_[i].size(); ++j) {
				if (!rnd.randBool(rbool_) || (vec_[i][j] == vec_[i][j - 1] && vec_[i][j] == vec_[i - 1][j])) continue;
				if (vec_[i][j]) vec_[i][j] = false;
				else vec_[i][j] = true;
			}
	}
	template<typename STL_, typename Int_>
	constexpr void noiseShore(STL_& vec_, const double rbool_, const Int_ true_tile_ = 1, const Int_ false_tile_ = 0) {
		for (std::size_t i{ 1 }; i < vec_.size(); ++i)
			for (std::size_t j{ 1 }; j < vec_[i].size(); ++j) {
				if (!rnd.randBool(rbool_) || (vec_[i][j] == vec_[i][j - 1] && vec_[i][j] == vec_[i - 1][j])) continue;
				if (vec_[i][j]) vec_[i][j] = false_tile_;
				else vec_[i][j] = true_tile_;
			}
	}
}