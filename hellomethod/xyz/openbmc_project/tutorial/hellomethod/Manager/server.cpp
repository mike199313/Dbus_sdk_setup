#include <algorithm>
#include <map>
#include <sdbusplus/exception.hpp>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/sdbuspp_support/server.hpp>
#include <sdbusplus/server.hpp>
#include <string>
#include <tuple>

#include <xyz/openbmc_project/tutorial/hellomethod/Manager/server.hpp>


namespace sdbusplus
{
namespace xyz
{
namespace openbmc_project
{
namespace tutorial
{
namespace hellomethod
{
namespace server
{

Manager::Manager(bus_t& bus, const char* path)
        : _xyz_openbmc_project_tutorial_hellomethod_Manager_interface(
                bus, path, interface, _vtable, this), _intf(bus.getInterface())
{
}


int Manager::_callback_Commit(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    auto o = static_cast<Manager*>(context);

    {
        return sdbusplus::sdbuspp::method_callback(
                msg, o->_intf, error,
                std::function(
                    [=](int32_t&& transactionId, std::string&& msg)
                    {
                        return o->commit(
                                transactionId, msg);
                    }
                ));
    }

    return 0;
}

namespace details
{
namespace Manager
{
static const auto _param_Commit =
        utility::tuple_to_array(message::types::type_id<
                int32_t, std::string>());
static const auto _return_Commit =
        utility::tuple_to_array(std::make_tuple('\0'));
}
}




const vtable_t Manager::_vtable[] = {
    vtable::start(),

    vtable::method("Commit",
                   details::Manager::_param_Commit
                        .data(),
                   details::Manager::_return_Commit
                        .data(),
                   _callback_Commit),
    vtable::end()
};

} // namespace server
} // namespace hellomethod
} // namespace tutorial
} // namespace openbmc_project
} // namespace xyz
} // namespace sdbusplus

