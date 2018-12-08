#pragma once
//SimpleVoronoiIsland
#include "Random.hpp"
#include <vector>
#include <cstdint>
#include <utility>

namespace dtl {

	template<typename PointT>
	constexpr std::int_fast32_t distanceSqrd(const PointT& point_, std::int_fast32_t x_, std::int_fast32_t y_) {
		x_ -= (std::int_fast32_t)point_.first;
		y_ -= (std::int_fast32_t)point_.second;
		return (x_ * x_) + (y_ * y_);
	}

	template<typename Int>
	class SimpleVoronoiIsland {
	public:
		//コンストラクタ
		SimpleVoronoiIsland() = default;
		template<typename T_>
		constexpr SimpleVoronoiIsland(T_& t_, const std::size_t count_ = 100, const double rbool_ = 0.4, const Int land_ = 1, const Int sea_ = 0) {
			create(t_, count_, rbool_, land_, sea_);
		}

		//ボロノイ図を作る
		template<typename T_>
		constexpr void create(T_& t_, const std::size_t count_ = 100, const double rbool_ = 0.4, const Int land_ = 1, const Int sea_ = 0) {
			for (std::size_t i{}; i < count_; ++i) {
				createPoint((t_.empty()) ? 0 : t_.front().size(), t_.size(), rbool_, land_, sea_);
			}
			createSites(t_, (t_.empty()) ? 0 : t_.front().size(), t_.size());
		}
		constexpr void init() {
			point.clear();
			color.clear();
		}
	private:
		std::vector<std::pair<std::size_t, std::size_t>> point;
		std::vector<Int> color;

		constexpr bool isMakeIsland(const std::size_t w_, const std::size_t h_, const std::size_t numerator_, const std::size_t denominator_) const {
			return (point.back().first > (w_ * numerator_ / denominator_) && point.back().first < (w_ * (denominator_ - numerator_) / denominator_)) && (point.back().second > (h_ * numerator_ / denominator_) && point.back().second < (h_ * (denominator_ - numerator_) / denominator_));
		}
		//原点の場所と陸地を決定する
		constexpr void createPoint(const std::size_t w_, const std::size_t h_, const double rbool_, const Int land_, const Int sea_) {
			point.emplace_back((std::size_t)rnd((std::int_fast32_t)w_), (std::size_t)rnd((std::int_fast32_t)h_));
			if (isMakeIsland(w_, h_, 2, 5) || (rnd.randBool(rbool_) && isMakeIsland(w_, h_, 1, 5)))
				color.emplace_back(land_);
			else color.emplace_back(sea_);
		}
		//図形を線画
		template<typename T_>
		constexpr void createSites(T_& t_, const std::size_t w_, const std::size_t h_)const {
			std::int_fast32_t ds{}, dist{};
			for (std::size_t hh{}, ind{}; hh < h_; ++hh)
				for (std::size_t ww{}; ww < w_; ++ww) {
					ind = std::numeric_limits<std::size_t>::max();
					dist = std::numeric_limits<std::int_fast32_t>::max();
					for (std::size_t it{}; it < point.size(); ++it) {
						const std::pair<std::size_t, std::size_t>& p{ point[it] };
						if ((ds = distanceSqrd(p, (std::int_fast32_t)ww, (std::int_fast32_t)hh)) >= dist) continue;
						dist = ds;
						ind = it;
					}
					if (ind != std::numeric_limits<std::size_t>::max()) t_[hh][ww] = color[ind];
				}
		}
	};
}
