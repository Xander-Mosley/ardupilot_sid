
/*
  external control library for plane
 */
#pragma once

#include <AP_ExternalControl/AP_ExternalControl.h>

#if AP_EXTERNAL_CONTROL_ENABLED

#include <AP_Common/Location.h>

class AP_ExternalControl_Plane : public AP_ExternalControl {
public:
    SurfaceExcitation::Output surface_excitation_output() override;
    void surface_excitation_submit(const SurfaceExcitation::Command &cmd) override;
    void surface_excitation_disconnect() override;
    SurfaceExcitation::Status surface_excitation_status() override;

    /*
        Sets the target global position for a loiter point.
    */
    bool set_global_position(const Location& loc) override WARN_IF_UNUSED;
};

#endif // AP_EXTERNAL_CONTROL_ENABLED
