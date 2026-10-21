#pragma once
#include <AP_Param/AP_Param.h>
#include <AP_HAL/Semaphores.h>
#include <AP_SurfaceExcitation/SurfaceExcitation.h>

class PlaneSurfaceExcitation {
public:
    PlaneSurfaceExcitation() { AP_Param::setup_object_defaults(this, var_info); }
    static const AP_Param::GroupInfo var_info[];
    void submit(const SurfaceExcitation::Command &command);
    void disconnect();
    SurfaceExcitation::Status get_status();
    SurfaceExcitation::Output get_output();
    void prepare(float *outputs);
    void finish(const float *outputs, bool accepted);
private:
    AP_Int8 enabled;
    AP_Float max_roll, max_pitch, max_yaw, max_surface, slew;
    AP_Int16 timeout_ms, return_ms;
    HAL_Semaphore sem;
    SurfaceExcitation::Command pending{};
    SurfaceExcitation::Status published{};
    SurfaceExcitation::Output published_output{};
    SurfaceExcitation::Engine engine;
    bool have_pending{}, disconnected{}, disable_pending{}, configured{};
    uint32_t config_hash{}, revision{};
    uint64_t last_clock{}, last_mono{};
    uint64_t last_config_log{};
    uint8_t last_state{255}, last_reason{255};
    SurfaceExcitation::Settings settings() const;
};
