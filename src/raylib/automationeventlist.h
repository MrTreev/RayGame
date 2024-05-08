#pragma once

#include "raylib/raylib.h"

namespace raylib {
class AutomationEventList: public ::AutomationEventList {
public:
    AutomationEventList( //NOLINT: hicpp-explicit-conversion
        const ::AutomationEventList& automationEventList
    );

    explicit AutomationEventList(
        unsigned int     _capacity = 16'384,
        unsigned int     _count    = 0,
        AutomationEvent* _events   = nullptr
    );

    explicit AutomationEventList(const char* fileName);
    AutomationEventList(const AutomationEventList&) = delete;
    AutomationEventList(AutomationEventList&& other) noexcept;
    AutomationEventList& operator=(const AutomationEventList&) = delete;
    AutomationEventList& operator=(AutomationEventList&& other) noexcept;
    ~AutomationEventList();

    AutomationEventList& operator=(const ::AutomationEventList& other);

    void Load(const char* fileName);
    void Unload();
    bool IsReady();
    bool Export(const char* fileName);
    void Set();
    void SetBaseFrame(int frame);
    void StartRecording();
    void StopRecording();
    void Play(int index);

    unsigned int     GetCapacity() const;
    unsigned int     GetCount() const;
    AutomationEvent* GetEvents() const;

protected:
    void set(const ::AutomationEventList& other);
};
} // namespace raylib
