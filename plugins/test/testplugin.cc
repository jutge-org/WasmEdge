#include "testplugin.h"

namespace WasmEdge {
namespace Host {
namespace {

Runtime::Instance::ModuleInstance *
create(const Plugin::PluginModule::ModuleDescriptor *) noexcept {
  // There can be several modules in a plug-in. For that, developers should
  // implement several `create` functions for each module.
  return new WasmEdgePluginTestModule;
}

Plugin::Plugin::PluginDescriptor Descriptor{
    // Plug-in name - for searching the plug-in context by the
    // `WasmEdge_PluginFind()` C API.
    .Name = "wasmedge_plugintest_cpp",
    // Plug-in description.
    .Description = "",
    // Plug-in API version.
    .APIVersion = Plugin::Plugin::CurrentAPIVersion,
    // Plug-in version.
    .Version = {0, 10, 0, 0},
    // Module count in this plug-in.
    .ModuleCount = 1,
    // Pointer to module description array.
    .ModuleDescriptions =
        // The module descriptor array.
    (Plugin::PluginModule::ModuleDescriptor[]){
        {
            // Module name. This is the name for searching and creating the
            // module instance context by the
            // `WasmEdge_PluginCreateModule()` C API.
            .Name = "wasmedge_plugintest_cpp_module",
            // Module description.
            .Description = "This is for the plugin tests in WasmEdge.",
            // Creation function pointer.
            .Create = create,
        },
    },
    // Plug-in options (Work in progress).
    .AddOptions = nullptr,
};

EXPORT_GET_DESCRIPTOR(Descriptor)

} // namespace
} // namespace Host
} // namespace WasmEdge