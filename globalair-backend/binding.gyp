{
  "targets": [
    {
      "target_name": "core_addon",
      "sources": [
        "../globalair-cpp-core/cpp/main.cpp",
        "../globalair-cpp-core/cpp/baggage/baggage_system.cpp",
        "../globalair-cpp-core/cpp/dashboard/monitor_dashboard.cpp",
        "../globalair-cpp-core/cpp/delay/delay_analyzer.cpp",
        "../globalair-cpp-core/cpp/gate/gate_allocator.cpp",
        "../globalair-cpp-core/cpp/graph/graph.cpp",
        "../globalair-cpp-core/cpp/graph/shortest_path.cpp",
        "../globalair-cpp-core/cpp/lost/lost_tracker.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "conditions": [
        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": { "ExceptionHandling": 1 }
          }
        }]
      ]
    }
  ]
}