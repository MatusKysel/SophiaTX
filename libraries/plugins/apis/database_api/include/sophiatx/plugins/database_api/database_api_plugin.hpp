#pragma once
#include <sophiatx/plugins/chain/chain_plugin.hpp>
#include <sophiatx/plugins/json_rpc/json_rpc_plugin.hpp>

#include <appbase/application.hpp>

namespace sophiatx { namespace plugins { namespace database_api {

using namespace appbase;

#define SOPHIATX_DATABASE_API_PLUGIN_NAME "database_api"

class database_api_plugin : public plugin< database_api_plugin >
{
   public:
      database_api_plugin();
      virtual ~database_api_plugin();

      APPBASE_PLUGIN_REQUIRES(
         (sophiatx::plugins::json_rpc::json_rpc_plugin)
         (sophiatx::plugins::chain::chain_plugin)
      )

      static const std::string& name() { static std::string name = SOPHIATX_DATABASE_API_PLUGIN_NAME; return name; }

      static void set_program_options(
         options_description& cli,
         options_description& cfg );
      virtual void plugin_initialize( const variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;

      std::shared_ptr< class database_api > api;
};

} } } // sophiatx::plugins::database_api
