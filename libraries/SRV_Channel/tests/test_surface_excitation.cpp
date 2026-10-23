#include <AP_gtest.h>
#include <SRV_Channel/SRV_Channel.h>
const AP_HAL::HAL& hal = AP_HAL::get_HAL();
static SRV_Channels servos;
static SRV_Channel *configure(uint8_t channel, float minimum=1100, float trim=1500, float maximum=1900, float reverse=0)
{
    auto *ch=SRV_Channels::srv_channel(channel);
    AP_Param::set_object_value(ch, SRV_Channel::var_info, "FUNCTION", SRV_Channel::k_aileron);
    AP_Param::set_object_value(ch, SRV_Channel::var_info, "MIN", minimum);
    AP_Param::set_object_value(ch, SRV_Channel::var_info, "TRIM", trim);
    AP_Param::set_object_value(ch, SRV_Channel::var_info, "MAX", maximum);
    AP_Param::set_object_value(ch, SRV_Channel::var_info, "REVERSED", reverse);
    SRV_Channels::update_aux_servo_function();
    ch->set_angle(4500);
    SRV_Channels::set_emergency_stop(false);
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron,1125);
    return ch;
}
TEST(SurfaceExcitation, CalibratedAdditionAndNoLatch)
{
    auto *ch=configure(0);
    float delta[NUM_SERVO_CHANNELS]{};delta[0]=450;
    EXPECT_TRUE(SRV_Channels::calc_pwm(delta));
    EXPECT_EQ(ch->get_output_pwm(),1640);
    EXPECT_EQ(ch->excitation_result.baseline,1600);
    EXPECT_EQ(ch->excitation_result.applied_delta,40);
    SRV_Channels::calc_pwm();EXPECT_EQ(ch->get_output_pwm(),1600);
    delta[0]=-450;SRV_Channels::calc_pwm(delta);EXPECT_EQ(ch->get_output_pwm(),1560);
}
TEST(SurfaceExcitation, AsymmetricAcrossTrimAndReversal)
{
    auto *ch=configure(0,1000,1400,1900);
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron,-450);
    float delta[NUM_SERVO_CHANNELS]{};delta[0]=900;
    SRV_Channels::calc_pwm(delta);EXPECT_EQ(ch->get_output_pwm(),1460);
    configure(0,1000,1400,1900,1);
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron,0);
    delta[0]=450;SRV_Channels::calc_pwm(delta);EXPECT_EQ(ch->get_output_pwm(),1360);
    delta[0]=-450;SRV_Channels::calc_pwm(delta);EXPECT_EQ(ch->get_output_pwm(),1450);
}
TEST(SurfaceExcitation, SaturationDuplicateAndEmergencyStop)
{
    auto *ch=configure(0);auto *other=configure(1,1000,1400,2000);
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron,4400);
    float delta[NUM_SERVO_CHANNELS]{};delta[0]=delta[1]=450;
    SRV_Channels::calc_pwm(delta);EXPECT_EQ(ch->get_output_pwm(),1900);EXPECT_TRUE(ch->excitation_result.clipped);
    EXPECT_EQ(other->get_output_pwm(),2000);
    SRV_Channels::set_emergency_stop(true);
    EXPECT_FALSE(SRV_Channels::calc_pwm(delta));EXPECT_EQ(ch->excitation_result.applied_delta,0);
    SRV_Channels::set_emergency_stop(false);
}
TEST(SurfaceExcitation, RawOverrideRejectsWholeVector)
{
    auto *ch=configure(0);auto *other=configure(1);
    SRV_Channels::set_output_pwm_chan(0,1700);
    float delta[NUM_SERVO_CHANNELS]{};delta[0]=delta[1]=450;
    EXPECT_FALSE(SRV_Channels::calc_pwm(delta));EXPECT_EQ(ch->get_output_pwm(),1700);
    EXPECT_EQ(other->excitation_result.applied_delta,0);
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron,0);
}
AP_GTEST_MAIN()
