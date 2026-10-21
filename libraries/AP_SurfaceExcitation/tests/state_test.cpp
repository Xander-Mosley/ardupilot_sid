#include "../SurfaceExcitation.h"
#include <cassert>
#include <limits>
using namespace SurfaceExcitation;
static Command sample(uint32_t seq, bool enable, uint64_t t, float r=0.1f) {
    Command c{}; c.sequence=seq;c.enable=enable;c.stamp_us=t;c.received_us=t;c.axis[0]=r;return c;
}
int main() {
    Settings s; Engine e;
    assert(!e.accept(sample(1,true,1000000),1000000,1000000,s));
    assert(e.accept(sample(2,false,1000000),1000000,1000000,s));
    e.tick(1000000,true,s); assert(e.status.state==ARMED);
    assert(e.accept(sample(3,true,1010000,1),1010000,1010000,s));
    e.tick(1010000,true,s); assert(e.status.applied[0]==0.1f && e.status.clips==1);
    assert(!e.accept(sample(3,true,1020000),1020000,1020000,s));
    assert(!e.accept(sample(2,true,1020000),1020000,1020000,s));
    auto invalid=sample(4,true,1020000); invalid.axis[1]=std::numeric_limits<float>::quiet_NaN();
    assert(!e.accept(invalid,1020000,1020000,s));
    assert(!e.accept(sample(4,true,1),1020000,1020000,s));
    e.tick(1210001,true,s); assert(e.status.state==TIMEOUT);
    e.tick(1310001,true,s); assert(fabsf(e.status.applied[0]-0.05f)<1e-6);
    e.tick(1410001,true,s); assert(e.status.applied[0]==0);
    assert(!e.accept(sample(5,true,1420000),1420000,1420000,s));
    assert(e.accept(sample(0xfffffffeU,false,1430000),1430000,1430000,s));
    assert(e.accept(sample(0xffffffffU,true,1440000),1440000,1440000,s));
    assert(e.accept(sample(0,true,1450000),1450000,1450000,s));
    e.tick(1450000,true,s); e.tick(1460000,false,s); assert(e.status.applied[0]==0);
    for (const auto reason : {CLOCK, DISCONNECTED, CONFIG, OVERRIDE}) {
        e.fault(reason);
        assert(e.status.state==FAULT && !e.output_active());
        assert(!e.accept(sample(1,true,2000000),2000000,2000000,s));
        assert(e.accept(sample(1,false,2000000),2000000,2000000,s));
        auto simultaneous=sample(2,true,2010000);
        simultaneous.axis[1]=-.05f; simultaneous.axis[2]=.02f;
        assert(e.accept(simultaneous,2010000,2010000,s));
        e.tick(2010000,true,s);
        assert(e.status.applied[1]==-.05f && e.status.applied[2]==.02f);
        assert(e.accept(sample(3,false,2020000),2020000,2020000,s));
        e.tick(2120000,true,s);
        assert(fabsf(e.status.applied[0]-.05f)<1e-6f);
        e.tick(2220000,true,s);assert(!e.output_active());
    }
    e.disable(); assert(e.status.state==DISABLED && !e.output_active());
    float l,r; mix(450,900,0,0.5,l,r);assert(l==225 && r==675);
    mix(450,900,20,0.5,l,r);assert(fabsf(l-180)<0.01f && fabsf(r-720)<0.01f);
    mix(450,900,-20,0.5,l,r);assert(fabsf(l-315)<0.01f && fabsf(r-765)<0.01f);
    mix(4500,4500,0,1,l,r);assert(l==0 && r==4500);
    s.maximum[0]=std::numeric_limits<float>::infinity(); assert(!s.valid());
}
