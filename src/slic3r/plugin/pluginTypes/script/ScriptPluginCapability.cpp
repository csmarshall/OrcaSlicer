#include "ScriptPluginCapability.hpp"

#include "ScriptPluginCapabilityTrampoline.hpp"

#include <boost/log/trivial.hpp>
#include <memory>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "slic3r/plugin/PluginManager.hpp"
#include "slic3r/plugin/PythonPluginInterface.hpp"

namespace py = pybind11;

namespace Slic3r {
void ScriptPluginCapability::RegisterBindings(pybind11::module_& module)
{
    BOOST_LOG_TRIVIAL(debug) << "Registering orca.script bindings";

    auto script = module.def_submodule("script", "Script Plugins API");

    py::class_<ScriptPluginCapability, PluginCapabilityInterface, PyScriptPluginCapabilityTrampoline, std::shared_ptr<ScriptPluginCapability>>(script, "ScriptPluginCapabilityBase")
        .def(py::init<>())
        .def("get_type", &ScriptPluginCapability::get_type)
        .def("execute", &ScriptPluginCapability::execute);

    script.def("cancel_requested", &ScriptAsyncRuntime::cancel_requested,
               "True when the Script invocation running on the calling thread has been asked to stop "
               "(plugin unload, application shutdown or capability disable). Poll it from a long-running "
               "execute() and return when it becomes true. Returns False outside an invocation and on "
               "threads the plugin started itself.");
}
} // namespace Slic3r
