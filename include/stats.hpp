#pragma once

#include <map>
#include <string>

#include "logger.hpp"
#include "vector.hpp"


namespace sgtr
{

template <typename T>
class Stats
{
private:
    using bins_t = std::map<T, size_t>;

    size_t total_;
    bins_t bins_;

public:
    Stats(size_t total)
        : total_(total){};

    ~Stats() = default;

    void print()
    {
        size_t sum{0};

        LOG(INFO) << "Map statistics: ";
        for (const auto& el : bins_)
        {
            sum += el.second;
            float percentage = (static_cast<float>(el.second) / total_) * 100.0f;
            LOG(INFO) << el.first << " : " << percentage << "%";
        }

        if (total_ != sum)
            LOG(WARN) << "Stats sum != total, something went wrong? " << sum << " vs " << total_;
    }

    void count(T obj)
    {
        auto it = bins_.find(obj);
        if (it != bins_.end())
            (*it).second++;
        else
            bins_[obj] = 1UL;
    }

    void reset()
    {
        bins_.clear();
        bins_t bins;
        std::swap(bins, bins_);
    }
};

} // namespace sgtr