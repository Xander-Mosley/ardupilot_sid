/*
  external control library for plane
 */


#include "AP_ExternalControl_Plane.h"
#if AP_EXTERNAL_CONTROL_ENABLED

#include "Plane.h"
SurfaceExcitation::Output AP_ExternalControl_Plane::surface_excitation_output() { return plane.g2.surface_excitation.get_output(); }
void AP_ExternalControl_Plane::surface_excitation_submit(const SurfaceExcitation::Command &cmd) { plane.g2.surface_excitation.submit(cmd); }
void AP_ExternalControl_Plane::surface_excitation_disconnect() { plane.g2.surface_excitation.disconnect(); }
SurfaceExcitation::Status AP_ExternalControl_Plane::surface_excitation_status() { return plane.g2.surface_excitation.get_status(); }


/*
  Sets the target global position for a loiter point.
*/
bool AP_ExternalControl_Plane::set_global_position(const Location& loc)
{

    // set_target_location already checks if plane is ready for external control.
    // It doesn't check if flying or armed, just that it's in guided mode.
    return plane.set_target_location(loc);
}

#endif // AP_EXTERNAL_CONTROL_ENABLED
