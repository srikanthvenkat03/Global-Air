#include "lost_tracker.h"

void LostTracker::add_baggage(const BaggageInfo& info) {
    if (baggage_map.count(info.id)) {
        return; // Already tracking
    }
    baggage_flow.push_front(info);
    baggage_map[info.id] = baggage_flow.begin();
}

bool LostTracker::update_checkpoint(const std::string& baggageId, const std::string& newCheckpoint) {
    if (baggage_map.count(baggageId)) {
        baggage_map[baggageId]->last_known_checkpoint = newCheckpoint;
        return true;
    }
    return false;
}

BaggageInfo LostTracker::get_baggage_info(const std::string& baggageId) {
    if (baggage_map.count(baggageId)) {
        return *baggage_map[baggageId];
    }
    return BaggageInfo(); // Return empty info if not found
}

bool LostTracker::is_tracking(const std::string& baggageId) {
    return baggage_map.count(baggageId) > 0;
}