#include "core/raycpp/automationeventlist.h"
#include "core/raycpp/raylibexception.h"

void core::raycpp::AutomationEventList::set(const ::AutomationEventList& other) {
    capacity = other.capacity;
    count    = other.count;
    events   = other.events;
}

core::raycpp::AutomationEventList::AutomationEventList(
    const ::AutomationEventList& automationEventList
) {
    set(automationEventList);
}

core::raycpp::AutomationEventList::AutomationEventList(
    unsigned int     _capacity,
    unsigned int     _count,
    AutomationEvent* _events
)
    : ::AutomationEventList{_capacity, _count, _events} {}

core::raycpp::AutomationEventList::AutomationEventList(const char* fileName) {
    Load(fileName);
}

core::raycpp::AutomationEventList::AutomationEventList(AutomationEventList&& other
) noexcept {
    set(other);

    other.capacity = 0;
    other.count    = 0;
    other.events   = nullptr;
}

core::raycpp::AutomationEventList::~AutomationEventList() {
    Unload();
}

core::raycpp::AutomationEventList&
core::raycpp::AutomationEventList::operator=(const ::AutomationEventList& other) {
    set(other);
    return *this;
}

core::raycpp::AutomationEventList&
core::raycpp::AutomationEventList::operator=(AutomationEventList&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.capacity = 0;
    other.count    = 0;
    other.events   = nullptr;

    return *this;
}

void core::raycpp::AutomationEventList::Load(const char* fileName) {
    Unload();
    set(::LoadAutomationEventList(fileName));
    if (!IsReady()) {
        throw RaylibException("Failed to load automation event list");
    }
}

void core::raycpp::AutomationEventList::Unload() {
#if RAYLIB_VERSION_MAJOR >= 5
#    if RAYLIB_VERSION_MINOR == 0
    ::UnloadAutomationEventList(this);
#    elif RAYLIB_VERSION_MINOR >= 1
    ::UnloadAutomationEventList(*this);
#    endif
#endif
}

bool core::raycpp::AutomationEventList::IsReady() {
    return events != nullptr;
}

bool core::raycpp::AutomationEventList::Export(const char* fileName) {
    return ::ExportAutomationEventList(*this, fileName);
}

void core::raycpp::AutomationEventList::Set() {
    ::SetAutomationEventList(this);
}

void core::raycpp::AutomationEventList::SetBaseFrame(int frame) {
    Set();
    ::SetAutomationEventBaseFrame(frame);
}

void core::raycpp::AutomationEventList::StartRecording() {
    Set();
    ::StartAutomationEventRecording();
}

void core::raycpp::AutomationEventList::StopRecording() {
    Set();
    ::StopAutomationEventRecording();
}

void core::raycpp::AutomationEventList::Play(int index) {
    if (index < 0 || static_cast<unsigned int>(index) >= this->count) {
        return;
    }

    Set();
    ::PlayAutomationEvent(this->events[index]);
}

unsigned int core::raycpp::AutomationEventList::GetCapacity() const {
    return capacity;
}

unsigned int core::raycpp::AutomationEventList::GetCount() const {
    return count;
}

AutomationEvent* core::raycpp::AutomationEventList::GetEvents() const {
    return events;
}
