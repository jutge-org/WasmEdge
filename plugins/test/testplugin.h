#pragma once

#include "plugin/plugin.h"

#include <cstdint>
#include <string>

namespace WasmEdge {
namespace Host {

// The environment class. For the register object.
class WasmEdgePluginTestEnv {
public:
  WasmEdgePluginTestEnv() noexcept = default;
};

// The host function base template class. For inheriting the environment class
// reference.
template <typename T>
class WasmEdgePluginTestFunc : public Runtime::HostFunction<T> {
public:
  WasmEdgePluginTestFunc(WasmEdgePluginTestEnv &HostEnv)
      : Runtime::HostFunction<T>(0), Env(HostEnv) {}

protected:
  WasmEdgePluginTestEnv &Env;
};

// The host function to add 2 int32_t numbers.
class WasmEdgePluginTestFuncAdd
    : public WasmEdgePluginTestFunc<WasmEdgePluginTestFuncAdd> {
public:
  WasmEdgePluginTestFuncAdd(WasmEdgePluginTestEnv &HostEnv)
      : WasmEdgePluginTestFunc(HostEnv) {}
  Expect<uint32_t> body(const Runtime::CallingFrame &, uint32_t A, uint32_t B) {
    return A + B;
  }
};

// The host function to sub 2 int32_t numbers.
class WasmEdgePluginTestFuncSub
    : public WasmEdgePluginTestFunc<WasmEdgePluginTestFuncSub> {
public:
  WasmEdgePluginTestFuncSub(WasmEdgePluginTestEnv &HostEnv)
      : WasmEdgePluginTestFunc(HostEnv) {}
  Expect<uint32_t> body(const Runtime::CallingFrame &, uint32_t A, uint32_t B) {
    return A - B;
  }
};

// The host module class. There can be several modules in a plug-in.
class WasmEdgePluginTestModule : public Runtime::Instance::ModuleInstance {
public:
  WasmEdgePluginTestModule()
      : Runtime::Instance::ModuleInstance("wasmedge_plugintest_cpp_module") {
    addHostFunc("add", std::make_unique<WasmEdgePluginTestFuncAdd>(Env));
    addHostFunc("sub", std::make_unique<WasmEdgePluginTestFuncSub>(Env));
  }

  WasmEdgePluginTestEnv &getEnv() { return Env; }

private:
  WasmEdgePluginTestEnv Env;
};

} // namespace Host
} // namespace WasmEdge