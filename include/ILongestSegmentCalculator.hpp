#pragma once

class ILongestSegmentCalculator {
public:
    virtual ~ILongestSegmentCalculator() = default;

    virtual int longestSegment() const = 0;
};
