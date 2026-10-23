// Standalone test: c++ -std=c++11 air_data_native.cpp -o /tmp/test-air-data
#include "../AirData.h"
#include <cassert>
#include <initializer_list>
#include <limits>
int main()
{
    using namespace AP_AirData;
    for (int rate : {20, 50, 100}) {
        assert(rate_hz(rate) == rate);
        assert(!due(1000/rate-1, 0, rate));
        assert(due(1000/rate, 0, rate));
    }
    assert(rate_hz(0) == 20 && rate_hz(99) == 20 && rate_hz(-1) == 20);
    assert(due(10, UINT32_MAX-10, 50));
    assert(flow_flags(20,1,2) == 14);
    assert(flow_flags(1,0,0) == 10);
    assert(flow_flags(-20,0,0) == 6);
    assert(flow_flags(std::numeric_limits<float>::quiet_NaN(),0,0) == 0);
    assert(fabsf(alpha(20,2) - atanf(.1f)) < 1e-6);
    assert(alpha(20,-2) < 0 && beta(20,-2,1) < 0);
    assert(fabsf(beta(20,2,1) - asinf(2/sqrtf(405))) < 1e-6);
    assert(alpha(-20,2) == 0);
    return 0;
}
