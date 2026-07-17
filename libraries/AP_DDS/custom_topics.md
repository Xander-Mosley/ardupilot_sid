# Adding Custom DDS Topics to ArduPilot

This guide explains how to create and publish your own custom DDS topics from ArduPilot using the AP_DDS library.

> **Prerequisites**
>
> - A recent version of the ArduPilot source code (or your own custom fork).
> - ROS 2 development environment.
> - `microxrceddsgen` installed.
> - A working AP_DDS build environment.

## Overview

> Adding a custom DDS topic consists of four major steps:
>
> 1. Create a custom ROS 2 message.
> 2. Generate the DDS serialization code.
> 3. Register the topic inside AP_DDS.
> 4. Implement the code that fills and publishes the message.

---

## Step 1 - Create the custom ROS 2 Message

Create a new `.msg` file inside:

```text
ardupilot/
└── Tools/
    └── ros2/
        └── ardupilot_msgs/
            └── msg/
```

For example:

```text
CustomMessage.msg
```

---

### a. Register the Message

Open:

```text
Tools/ros2/ardupilot_msgs/CMakeLists.txt
```

Add the new message to the list of generated interfaces ( rosidl_generate_interfaces(${PROJECT_NAME}) ).

For example:

```cmake
msg/CustomMessage.msg
```

---

### b. Rebuild ardupilot_msgs

The ROS message package must be rebuilt so ROS generates the corresponding DDS interface files.

If using the **ros_docker_template**, perform the following.

> i) Mount the ArduPilot Source
> Inside `docker-compose.yaml`, add the ArduPilot folder as a writable volume:
>
> ```yaml
> volumes:
>   - ./ardupilot:/develop_ws/ardupilot:rw
> ```
>
> ii) Build the Container
>
> ```bash
> docker compose build
> ```
>
> iii) Start the Container
>
> ```bash
> docker compose up -d
> ```
>
> iv) Enter the Development Container
>
> ```bash
> docker exec -it ros2_trajectory_docker-develop-1 bash
> ```
>
> v) Build the ROS Messages
>
> ```bash
> cd /ardupilot/Tools/ros2
> 
> colcon build --packages-select ardupilot_msgs
> ```
>
> vi) Exit
>
> ```bash
> exit
> ```
>
> vii) Stop the Container
>
> ```bash
> docker compose down
> ```

### c. Verify Generated Files

After rebuilding, a new `.idl` file should have been generated.

Look in:

```text
ardupilot/
└── Tools/
    └── ros2/
        └── install/
            └── ardupilot_msgs/
                └── share/
                    └── ardupilot_msgs/
                        └── msg/
```

You should now see something similar to:

```text
CustomMessage.msg
CustomMessage.idl
```

---

## Step 2 - Generate the DDS Serialization Code

### a. Copy the IDL Files

Copy every custom `.idl` file into:

```text
ardupilot/
└── libraries/
    └── AP_DDS/
        └── idl/
            └── ardupilot_msgs/
                └── msg/
```

---

### b. Generate the DDS Serialization Code

Change the directory to the ardupilot folder and ensure the target folder exists:

```bash
cd /ardupilot
mkdir -p build/sitl/libraries/AP_DDS/generated/ardupilot_msgs/msg
```

For each custom message, run:

```bash
microxrceddsgen \
    -cs \
    -replace \
    -default-container-prealloc-size 8 \
    -d build/sitl/libraries/AP_DDS/generated/ardupilot_msgs/msg \
    -I libraries/AP_DDS/Idl \
    libraries/AP_DDS/Idl/ardupilot_msgs/msg/CustomMessage.idl
```

Replace:

```text
CustomMessage.idl
```

with your own message.

---

### c. Verify Generated Source Files

The following files should now exist:

```text
ardupilot/
└── build/
    └── sitl/
        └── libraries/
            └── AP_DDS/
                └── generated/
                    └── ardupilot_msgs/
                        └── msg/
                            custom_message.c
                            custom_message.h
```

If these files were created successfully, the serialization code was generated correctly.

---

## Step 3 - Register the Topic Inside AP_DDS

### a. Enable the Publisher

Open:

```text
libraries/AP_DDS/AP_DDS_config.h
```

Add:

```cpp
#ifndef AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
#define AP_DDS_CUSTOMMESSAGE_PUB_ENABLED 1
#endif

#ifndef AP_DDS_DELAY_CUSTOMMESSAGE_TOPIC_MS
#define AP_DDS_DELAY_CUSTOMMESSAGE_TOPIC_MS 100
#endif
```

The delay specifies the publish interval in milliseconds.

For example:

| Delay  | Publish Rate |
|--------|-------------:|
| 100 ms | 10 Hz        |
| 20 ms  | 50 Hz        |
| 5 ms   | 200 Hz       |

---

### b. Register the Topic

Open:

```text
libraries/AP_DDS/AP_DDS_Topic_Table.h
```

Add the topic index:

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
LOCAL_CUSTOMMESSAGE_PUB,
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

Add the topic table entry:

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
    {
        .topic_id = to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB),
        .pub_id = to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB),
        .sub_id = to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB),
        .dw_id = uxrObjectId{.id = to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB), .type = UXR_DATAWRITER_ID},
        .dr_id = uxrObjectId{.id = to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB), .type = UXR_DATAREADER_ID},
        .topic_rw = Topic_rw::DataWriter,
        .topic_name = "custommessage",
        .type_name = "ardupilot_msgs::msg::dds_::CustomMessage_",
        .qos = {
            .durability = UXR_DURABILITY_VOLATILE,
            .reliability = UXR_RELIABILITY_BEST_EFFORT,
            .history = UXR_HISTORY_KEEP_LAST,
            .depth = 1,
        },
    },
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

### c. Add the Message to AP_DDS_Client.h

Open:

```text
libraries/AP_DDS/AP_DDS_Client.h
```

Include the generated header

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
#include "ardupilot_msgs/msg/CustomMessage.h"
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

Add the publisher members

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
    ardupilot_msgs_msg_CustomMessage tx_local_custommessage_topic;
    // The last ms timestamp AP_DDS wrote a custommessage message
    uint64_t last_custommessage_time_ms;
    //! @brief Serialize the current local custommessage and publish to the IO stream(s)
    void write_tx_local_custommessage_topic();
    static bool update_topic(ardupilot_msgs_msg_CustomMessage& msg);
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

## Step 4 - Implement the Publisher

Open:

```text
libraries/AP_DDS/AP_DDS_Client.cpp
```

---

### a. Include Additional Libraries

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
#include <...>
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

Include any libraries required to populate the message.

---

### b. Define the Publish Rate

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
static constexpr uint16_t DELAY_CUSTOMMESSAGE_TOPIC_MS =
    AP_DDS_DELAY_CUSTOMMESSAGE_TOPIC_MS;
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

### c. Implement update_topic()

This function gathers the desired ArduPilot data and fills the DDS message.

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
bool AP_DDS_Client::update_topic(ardupilot_msgs_msg_CustomMessage& msg)
{
    // Populate msg with data

    return true;
}
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

### d. Implement the Publish Function

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
void AP_DDS_Client::write_tx_local_custommessage_topic()
{
    WITH_SEMAPHORE(csem);
    if (connected) {
        ucdrBuffer ub {};
        const uint32_t topic_size = ardupilot_msgs_msg_CustomMessage_size_of_topic(&tx_local_custommessage_topic, 0);
        uxr_prepare_output_stream(&session, reliable_out, topics[to_underlying(TopicIndex::LOCAL_CUSTOMMESSAGE_PUB)].dw_id, &ub, topic_size);
        const bool success = ardupilot_msgs_msg_CustomMessage_serialize_topic(&ub, &tx_local_custommessage_topic);
        if (!success) {
            // TODO sometimes serialization fails on bootup. Determine why.
            // AP_HAL::panic("FATAL: DDS_Client failed to serialize\n");
        }
    }
}
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

### e. Publish the Topic Periodically

Inside the AP_DDS update loop, add:

```cpp
#if AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
    if (cur_time_ms - last_custommessage_time_ms > DELAY_CUSTOMMESSAGE_TOPIC_MS) {
        last_custommessage_time_ms = cur_time_ms;
        if (update_topic(tx_local_custommessage_topic)) {
            write_tx_local_custommessage_topic();
        }
    }
#endif //AP_DDS_CUSTOMMESSAGE_PUB_ENABLED
```

---

## Final Checklist

Before building ArduPilot, verify the following:

- ✅ Created a custom `.msg`
- ✅ Added the message to `CMakeLists.txt`
- ✅ Rebuilt `ardupilot_msgs`
- ✅ Copied the generated `.idl`
- ✅ Generated the DDS serialization code
- ✅ Verified the generated `.c` and `.h` files
- ✅ Added publisher configuration in `AP_DDS_config.h`
- ✅ Registered the topic in `AP_DDS_Topic_Table.h`
- ✅ Included the generated header in `AP_DDS_Client.h`
- ✅ Added publisher variables
- ✅ Implemented `update_topic()`
- ✅ Implemented the serialization function
- ✅ Added the periodic publish logic

---

## Notes

- Every custom message requires its own generated `.idl`, `.c`, and `.h` files.
- The DDS type name (`type_name`) **must exactly match** the generated type from `microxrceddsgen`.
- The topic name (`topic_name`) is the ROS 2 topic name that clients will subscribe to.
- `update_topic()` is responsible for gathering the desired flight data and filling the message before publication.
- Publish rates are controlled independently using the `AP_DDS_DELAY_<TOPIC>_TOPIC_MS` macro.
