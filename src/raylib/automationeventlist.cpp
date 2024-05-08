#include "raylib/automationeventlist.h"
#include "raylib/raylibexception.h"

void raylib::AutomationEventList::set(const ::AutomationEventList& other) {
    capacity = other.capacity;
    count    = other.count;
    events   = other.events;
}

raylib::AutomationEventList::AutomationEventList(
    const ::AutomationEventList& automationEventList
) {
    set(automationEventList);
}

raylib::AutomationEventList::AutomationEventList(
    unsigned int     _capacity,
    unsigned int     _count,
    AutomationEvent* _events
)
    : ::AutomationEventList{_capacity, _count, _events} {}

raylib::AutomationEventList::AutomationEventList(const char* fileName) {
    Load(fileName);
}

raylib::AutomationEventList::AutomationEventList(AutomationEventList&& other
) noexcept {
    set(other);

    other.capacity = 0;
    other.count    = 0;
    other.events   = nullptr;
}

raylib::AutomationEventList::~AutomationEventList() {
    Unload();
}

raylib::AutomationEventList&
raylib::AutomationEventList::operator=(const ::AutomationEventList& other) {
    set(other);
    return *this;
}

raylib::AutomationEventList&
raylib::AutomationEventList::operator=(AutomationEventList&& other) noexcept {
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

void raylib::AutomationEventList::Load(const char* fileName) {
    Unload();
    set(::LoadAutomationEventList(fileName));
    if (!IsReady()) {
        throw RaylibException("Failed to load automation event list");
    }
}

void raylib::AutomationEventList::Unload() {
#if RAYLIB_VERSION_MAJOR >= 5
#    if RAYLIB_VERSION_MINOR == 0
    ::UnloadAutomationEventList(this);
#    elif RAYLIB_VERSION_MINOR >= 1
    ::UnloadAutomationEventList(*this);
#    endif
#endif
}

bool raylib::AutomationEventList::IsReady() {
    return events != nullptr;
}

bool raylib::AutomationEventList::Export(const char* fileName) {
    return ::ExportAutomationEventList(*this, fileName);
}

void raylib::AutomationEventList::Set() {
    ::SetAutomationEventList(this);
}

void raylib::AutomationEventList::SetBaseFrame(int frame) {
    Set();
    ::SetAutomationEventBaseFrame(frame);
}

void raylib::AutomationEventList::StartRecording() {
    Set();
    ::StartAutomationEventRecording();
}

void raylib::AutomationEventList::StopRecording() {
    Set();
    ::StopAutomationEventRecording();
}

void raylib::AutomationEventList::Play(int index) {
    if (index < 0 || static_cast<unsigned int>(index) >= this->count) {
        return;
    }

    Set();
    ::PlayAutomationEvent(this->events[index]);
}

unsigned int raylib::AutomationEventList::GetCapacity() const {
    return capacity;
}

unsigned int raylib::AutomationEventList::GetCount() const {
    return count;
}

AutomationEvent* raylib::AutomationEventList::GetEvents() const {
    return events;
}
