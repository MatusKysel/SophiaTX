#include <sophiatx/plugins/template/template_plugin.hpp>
#include <sophiatx/plugins/template/template_api.hpp>
#include <sophiatx/plugins/template/template_objects.hpp>

namespace sophiatx { namespace plugins { namespace template_plugin {

namespace detail {

class template_api_impl
{
   public:
   template_api_impl() : _db( appbase::app().get_plugin< sophiatx::plugins::chain::chain_plugin >().db() ) {}

      example_call_return example_call( const example_call_args& args )const;

      chain::database& _db;
};

example_call_return template_api_impl::example_call( const example_call_args& args )const
{
   example_call_return final_result;

   final_result.sum = args.arg1 + args.arg2;
   final_result.mul = args.arg1 * args.arg2;

   return final_result;
}

} // detail

template_api::template_api(): my( new detail::template_api_impl() )
{
   JSON_RPC_REGISTER_API( SOPHIATX_PLUGIN_NAME );
}

template_api::~template_api() {}

DEFINE_READ_APIS( template_api, (example_call) )

} } } // sophiatx::plugins::template_plugin