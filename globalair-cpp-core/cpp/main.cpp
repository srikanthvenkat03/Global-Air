#include <nan.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>

// --- Include All Corrected C++ Core Headers ---
#include "graph/graph.h"
#include "graph/shortest_path.h"
#include "baggage/baggage_system.h"
#include "lost/lost_tracker.h"
#include "delay/delay_analyzer.h"
#include "gate/gate_allocator.h"
#include "dashboard/monitor_dashboard.h"

// --- Create persistent instances of classes ---
BaggageBST global_baggage_bst;
BaggageMinHeap global_baggage_heap;
LostTracker global_lost_tracker;
DelayAnalyzer global_delay_analyzer;
MonitorDashboard global_dashboard;

// --- 1. Shortest Path Function ---
NAN_METHOD(FindShortestPath) {
    if (info.Length() < 4) Nan::ThrowTypeError("Args: csvPath, start, end, weightType");
    Nan::Utf8String csv_path(info[0]);
    Nan::Utf8String start_node(info[1]);
    Nan::Utf8String end_node(info[2]);
    Nan::Utf8String weight_type(info[3]);
    Graph g;
    g.loadFromCSV(std::string(*csv_path));
    std::vector<std::string> path = ShortestPath::dijkstra(g, std::string(*start_node), std::string(*end_node), std::string(*weight_type));
    v8::Local<v8::Array> jsArray = Nan::New<v8::Array>(path.size());
    for (size_t i = 0; i < path.size(); i++) {
        Nan::Set(jsArray, i, Nan::New<v8::String>(path[i]).ToLocalChecked());
    }
    info.GetReturnValue().Set(jsArray);
}

// --- 2. Add Baggage Function ---
NAN_METHOD(AddBaggage) {
    if (info.Length() < 4) Nan::ThrowTypeError("Args: id, type, priority, risk");
    Nan::Utf8String id(info[0]);
    Nan::Utf8String type(info[1]);
    int priority = Nan::To<int>(info[2]).FromJust();
    int risk = Nan::To<int>(info[3]).FromJust();
    Baggage new_bag(std::string(*id), std::string(*type), priority, risk);
    
    global_baggage_bst.insert(new_bag);
    global_baggage_heap.push(new_bag);
    info.GetReturnValue().Set(Nan::New("Baggage added to C++ systems").ToLocalChecked());
}

// --- 3. Trace Lost Baggage Function ---
NAN_METHOD(TraceBaggage) {
    if (info.Length() < 1) Nan::ThrowTypeError("Args: baggageId");
    Nan::Utf8String id(info[0]);
    
    // Simulate a bag for testing if it's not already there
    if (!global_lost_tracker.is_tracking("BAG123")) {
        global_lost_tracker.add_baggage({"BAG123", "Checkpoint A", "Passenger A"});
        global_lost_tracker.update_checkpoint("BAG123", "Checkpoint B");
    }

    BaggageInfo bag_info = global_lost_tracker.get_baggage_info(std::string(*id));
    
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    if (!bag_info.id.empty()) {
        Nan::Set(obj, Nan::New("id").ToLocalChecked(), Nan::New(bag_info.id).ToLocalChecked());
        Nan::Set(obj, Nan::New("lastKnownLocation").ToLocalChecked(), Nan::New(bag_info.last_known_checkpoint).ToLocalChecked());
    } else {
        Nan::Set(obj, Nan::New("error").ToLocalChecked(), Nan::New("Baggage ID not found.").ToLocalChecked());
    }
    info.GetReturnValue().Set(obj);
}

// --- 4. Predict Delay Function ---
NAN_METHOD(PredictDelay) {
    if (info.Length() < 2) Nan::ThrowTypeError("Args: airport, month");
    Nan::Utf8String airport_str(info[0]);
    int month = Nan::To<int>(info[1]).FromJust();
    std::string airport = std::string(*airport_str);

    global_delay_analyzer.loadMockData(); 
    int avgDelay = global_delay_analyzer.getAvgDelay(airport, month);

    info.GetReturnValue().Set(Nan::New(avgDelay));
}

// --- 5. Allocate Gates Function ---
NAN_METHOD(AllocateGates) {
    if (!info[0]->IsArray()) Nan::ThrowTypeError("Argument must be an array of flights");
    v8::Local<v8::Array> flight_array = info[0].As<v8::Array>();
    std::vector<Flight> flights;
    for (uint32_t i = 0; i < flight_array->Length(); ++i) {
        v8::Local<v8::Object> js_flight = Nan::Get(flight_array, i).ToLocalChecked().As<v8::Object>();
        Nan::Utf8String id(Nan::Get(js_flight, Nan::New("id").ToLocalChecked()).ToLocalChecked());
        int priority = Nan::To<int>(Nan::Get(js_flight, Nan::New("priority").ToLocalChecked()).ToLocalChecked()).FromJust();
        flights.push_back({std::string(*id), priority});
    }

    GateAllocator allocator(flights); 
    allocator.sort_flights();
    std::map<std::string, int> allocations = allocator.allocate_gates();
    
    v8::Local<v8::Object> result = Nan::New<v8::Object>();
    for (const auto& pair : allocations) {
        Nan::Set(result, Nan::New(pair.first).ToLocalChecked(), Nan::New(pair.second));
    }
    info.GetReturnValue().Set(result);
}

// --- 6. Get Dashboard Summary ---
NAN_METHOD(GetDashboardSummary) {
    global_dashboard.record_delay("JFK-LHR", 20);
    global_dashboard.report_baggage_jam("T5-Belt3");

    std::vector<RouteDelay> top_delays = global_dashboard.get_top_delays(5);
    
    v8::Local<v8::Array> js_delays = Nan::New<v8::Array>(top_delays.size());
    for(size_t i = 0; i < top_delays.size(); ++i) {
        v8::Local<v8::Object> delay_obj = Nan::New<v8::Object>();
        Nan::Set(delay_obj, Nan::New("route").ToLocalChecked(), Nan::New(top_delays[i].route).ToLocalChecked());
        Nan::Set(delay_obj, Nan::New("delay").ToLocalChecked(), Nan::New(top_delays[i].totalDelay));
        Nan::Set(js_delays, i, delay_obj);
    }
    info.GetReturnValue().Set(js_delays);
}


// --- Module Initialization: Expose All Functions ---
NAN_MODULE_INIT(Initialize) {
    NAN_EXPORT(target, FindShortestPath);
    NAN_EXPORT(target, AddBaggage);
    NAN_EXPORT(target, TraceBaggage);
    NAN_EXPORT(target, PredictDelay);
    NAN_EXPORT(target, AllocateGates);
    NAN_EXPORT(target, GetDashboardSummary);
}

// --- Create the Addon ---
NODE_MODULE(core_addon, Initialize)