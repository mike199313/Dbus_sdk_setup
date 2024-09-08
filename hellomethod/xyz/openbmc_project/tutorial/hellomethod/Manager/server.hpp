#pragma once
#include <limits>
#include <map>
#include <optional>
#include <sdbusplus/sdbus.hpp>
#include <sdbusplus/server.hpp>
#include <sdbusplus/utility/dedup_variant.hpp>
#include <string>
#include <systemd/sd-bus.h>
#include <tuple>


#ifndef SDBUSPP_NEW_CAMELCASE
#define SDBUSPP_NEW_CAMELCASE 1
#endif

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

class Manager
{
    public:
        /* Define all of the basic class operations:
         *     Not allowed:
         *         - Default constructor to avoid nullptrs.
         *         - Copy operations due to internal unique_ptr.
         *         - Move operations due to 'this' being registered as the
         *           'context' with sdbus.
         *     Allowed:
         *         - Destructor.
         */
        Manager() = delete;
        Manager(const Manager&) = delete;
        Manager& operator=(const Manager&) = delete;
        Manager(Manager&&) = delete;
        Manager& operator=(Manager&&) = delete;
        virtual ~Manager() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Manager(bus_t& bus, const char* path);



        /** @brief Implementation for Commit
         *  You call this and a print should appear
         *
         *  @param[in] transactionId - Example allows for numbers and strings
         *  @param[in] msg - The msg that was sent
         */
        virtual void commit(
            int32_t transactionId,
            std::string msg) = 0;




        /** @brief Emit interface added */
        void emit_added()
        {
            _xyz_openbmc_project_tutorial_hellomethod_Manager_interface.emit_added();
        }

        /** @brief Emit interface removed */
        void emit_removed()
        {
            _xyz_openbmc_project_tutorial_hellomethod_Manager_interface.emit_removed();
        }

        static constexpr auto interface = "xyz.openbmc_project.tutorial.hellomethod.Manager";

    private:

        /** @brief sd-bus callback for Commit
         */
        static int _callback_Commit(
            sd_bus_message*, void*, sd_bus_error*);


        static const vtable_t _vtable[];
        sdbusplus::server::interface_t
                _xyz_openbmc_project_tutorial_hellomethod_Manager_interface;
        sdbusplus::SdBusInterface *_intf;


};


} // namespace server
} // namespace hellomethod
} // namespace tutorial
} // namespace openbmc_project
} // namespace xyz

namespace message::details
{
} // namespace message::details
} // namespace sdbusplus

